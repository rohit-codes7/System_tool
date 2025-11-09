#include "process.h"
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <algorithm>
#include <cctype>

static bool isNumberString(const std::string &s) {
    if (s.empty()) return false;
    for (char c : s) if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    return true;
}

std::vector<ProcInfo> getProcesses() {
    std::vector<ProcInfo> procs;
    DIR *dp = opendir("/proc");
    if (!dp) return procs;

    struct dirent *entry;
    long page_size_kb = sysconf(_SC_PAGESIZE) / 1024; // pagesize in KB
    long hz = sysconf(_SC_CLK_TCK);

    while ((entry = readdir(dp)) != nullptr) {
        std::string dname = entry->d_name;
        if (!isNumberString(dname)) continue;

        int pid = atoi(dname.c_str());
        std::string statPath = "/proc/" + dname + "/stat";
        std::ifstream statf(statPath);
        if (!statf) continue;

        std::string statline;
        std::getline(statf, statline);

        // Extract the command in parentheses and the rest
        size_t lp = statline.find('(');
        size_t rp = statline.rfind(')');
        std::string comm = "";
        std::string rest;
        if (lp != std::string::npos && rp != std::string::npos && rp > lp) {
            comm = statline.substr(lp + 1, rp - lp - 1);
            if (rp + 2 <= statline.size())
                rest = statline.substr(rp + 2);
        } else {
            // fallback parsing
            std::istringstream iss(statline);
            iss >> pid >> comm;
            std::getline(iss, rest);
        }

        std::istringstream rsss(rest);
        std::string tok;
        unsigned long long utime = 0, stime = 0;
        long rss_pages = 0;

        // fields after comm: state (1), then we need utime (13), stime (14), rss (22)
        for (int i = 1; i <= 22; ++i) {
            if (!(rsss >> tok)) break;
            if (i == 13) utime = std::stoull(tok);
            if (i == 14) stime = std::stoull(tok);
            if (i == 22) rss_pages = std::stol(tok);
        }

        // Try cmdline for full command line (null-separated)
        std::string cmdPath = "/proc/" + dname + "/cmdline";
        std::ifstream cmdf(cmdPath);
        std::string cmdline;
        if (cmdf) {
            std::getline(cmdf, cmdline, '\0');
        }
        std::string displayCmd = cmdline.empty() ? comm : cmdline;
        unsigned long rss_kb = (rss_pages > 0) ? (unsigned long)rss_pages * page_size_kb : 0;
        double cpu_time_seconds = (double)(utime + stime) / (double)hz;

        procs.push_back(ProcInfo{pid, displayCmd, rss_kb, cpu_time_seconds});
    }

    closedir(dp);

    // Sort by RSS (memory) descending
    std::sort(procs.begin(), procs.end(), [](const ProcInfo &a, const ProcInfo &b){
        return a.rss_kb > b.rss_kb;
    });

    return procs;
}