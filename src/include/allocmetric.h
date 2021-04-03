#include <iostream>

using namespace std;

namespace AllocMetric{
    static uint32_t totalAllocated;
    static uint32_t totalFreed;
    static uint32_t totalUsage() { return totalAllocated - totalFreed; };

    static void printUsage(){
        cout << "memory usage: " << totalUsage() << " bytes\n";
    }
}

void* operator new(size_t size){
    AllocMetric::totalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size){
    AllocMetric::totalFreed += size;
    free(memory);
}

void* operator new[](size_t size){
    AllocMetric::totalAllocated += size;
    return malloc(size);
}

void operator delete[](void* memory, size_t size){
    AllocMetric::totalFreed += size;
    free(memory);
}