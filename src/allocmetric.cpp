#include "include/allocmetric.h"

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