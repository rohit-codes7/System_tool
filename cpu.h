#ifndef CPU_H
#define CPU_H

#include <string>

struct CpuSnapshot {
    unsigned long long idle;
    unsigned long long total;
};

std::string getCpuModel();
CpuSnapshot readCpuSnapshot();
double calcCpuUsage(const CpuSnapshot &prev, const CpuSnapshot &curr);

#endif // CPU_H