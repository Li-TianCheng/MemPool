//
// Created by ltc on 2021/3/6.
//

#include "MemPool.h"

MemPool::MemPool(int num){
    for (int i = 0; i < 127; i++){
        mem.emplace_back(num, 8+i*4);
    }
}

void* MemPool::allocate(size_t size) {
    if (size < 8 || size > 512){
        return ::operator new(size);
    }
    return mem[(size-8)/4].allocate();
}

void MemPool::deallocate(void *ptr, size_t size) {
    if (size < 8 || size > 512){
        return ::operator delete(ptr);
    }
    mem[(size-8)/4].deallocate(ptr);
}

