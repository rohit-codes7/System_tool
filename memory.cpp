#include "memory.h"
#include <fstream>
#include <string>

MemInfo readMemInfo() {
    std::ifstream f("/proc/meminfo");
    std::string line;
    MemInfo mi{0, 0};
    while (std::getline(f, line)) {
        if (line.rfind("MemTotal:", 0) == 0) {
            unsigned long long val;
            if (sscanf(line.c_str(), "MemTotal: %llu kB", &val) == 1) mi.total_kb = val;
        } else if (line.rfind("MemAvailable:", 0) == 0) {
            unsigned long long val;
            if (sscanf(line.c_str(), "MemAvailable: %llu kB", &val) == 1) mi.available_kb = val;
        }
        if (mi.total_kb && mi.available_kb) break;
    }
    return mi;
}