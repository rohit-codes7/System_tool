#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

struct ProcInfo {
    int pid;
    std::string cmd;
    unsigned long rss_kb;
    double cpu_time_seconds;
};

std::vector<ProcInfo> getProcesses();

#endif // PROCESS_H