#ifndef MEMORY_H
#define MEMORY_H

struct MemInfo {
    unsigned long long total_kb;
    unsigned long long available_kb;
};

MemInfo readMemInfo();

#endif // MEMORY_H