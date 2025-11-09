#include "cpu.h"
#include <fstream>
#include <sstream>
#include <unistd.h>

std::string getCpuModel() {
    std::ifstream f("/proc/cpuinfo");
    std::string line;
    while (std::getline(f, line)) {
        if (line.find("model name") != std::string::npos) {
            auto pos = line.find(':');
            if (pos != std::string::npos)
                return line.substr(pos + 2);
        }
    }
    return "Unknown CPU";
}

CpuSnapshot readCpuSnapshot() {
    std::ifstream f("/proc/stat");
    std::string line;
    CpuSnapshot s{0, 0};
    if (std::getline(f, line)) {
        std::istringstream iss(line);
        std::string cpu;
        unsigned long long user = 0, nice = 0, system = 0, idle = 0, iowait = 0, irq = 0, softirq = 0, steal = 0;
        iss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
        unsigned long long total = user + nice + system + idle + iowait + irq + softirq + steal;
        s.idle = idle + iowait;
        s.total = total;
    }
    return s;
}

double calcCpuUsage(const CpuSnapshot &prev, const CpuSnapshot &curr) {
    unsigned long long idleDiff = curr.idle - prev.idle;
    unsigned long long totalDiff = curr.total - prev.total;
    if (totalDiff == 0) return 0.0;
    return (double)(totalDiff - idleDiff) * 100.0 / (double)totalDiff;
}