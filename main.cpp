#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <vector>
#include <sstream>
#include "cpu.h"
#include "memory.h"
#include "process.h"
#include <fstream>

static void clearScreen() {
    // ANSI escape to clear screen and move cursor to home
    std::cout << "\033[2J\033[H";
}

std::string formatUptime(unsigned long long seconds) {
    unsigned long long days = seconds / 86400;
    seconds %= 86400;
    unsigned long long hours = seconds / 3600;
    seconds %= 3600;
    unsigned long long minutes = seconds / 60;
    seconds %= 60;
    std::ostringstream oss;
    if (days) oss << days << "d ";
    oss << hours << "h " << minutes << "m " << seconds << "s";
    return oss.str();
}

unsigned long long readUptimeSeconds() {
    std::ifstream f("/proc/uptime");
    double up = 0;
    if (f) f >> up;
    return (unsigned long long) up;
}

int main() {
    // Take initial CPU snapshot
    CpuSnapshot prev = readCpuSnapshot();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    while (true) {
        CpuSnapshot curr = readCpuSnapshot();
        double cpuUsage = calcCpuUsage(prev, curr);
        prev = curr;

        MemInfo mi = readMemInfo();
        unsigned long long used_kb = (mi.total_kb > mi.available_kb) ? (mi.total_kb - mi.available_kb) : 0;

        unsigned long long uptime_s = readUptimeSeconds();

        std::vector<ProcInfo> procs = getProcesses();

        clearScreen();
        std::cout << "=== System Monitor ===\n\n";
        std::cout << "CPU: " << getCpuModel() << "\n";
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "CPU Usage: " << cpuUsage << "%\n\n";
        std::cout << "Memory: " << (mi.total_kb/1024) << " MB total, "
                  << (used_kb/1024) << " MB used, "
                  << (mi.available_kb/1024) << " MB available\n\n";
        std::cout << "Uptime: " << formatUptime(uptime_s) << "\n\n";

        // Header for processes
        std::cout << std::left << std::setw(8) << "PID"
                  << std::setw(30) << "COMMAND"
                  << std::setw(12) << "RSS(KB)"
                  << std::setw(12) << "CPU(s)" << "\n";
        std::cout << std::string(70, '-') << "\n";

        // Show top N processes by RSS (we sorted by RSS)
        int show = std::min(10, (int)procs.size());
        for (int i = 0; i < show; ++i) {
            const auto &p = procs[i];
            std::string cmd = p.cmd;
            if ((int)cmd.size() > 28) cmd = cmd.substr(0,25) + "...";
            std::cout << std::left << std::setw(8) << p.pid
                      << std::setw(30) << cmd
                      << std::setw(12) << p.rss_kb
                      << std::setw(12) << std::fixed << std::setprecision(2) << p.cpu_time_seconds
                      << "\n";
        }

        std::cout << "\n(Refresh every 2s)  Press Ctrl+C to exit.\n";

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}