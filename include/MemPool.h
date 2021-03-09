//
// Created by ltc on 2021/3/6.
//

#ifndef MEMPOOL_MEMPOOL_H
#define MEMPOOL_MEMPOOL_H

#include "ManageChunk.h"
#include "Mutex.h"
#include <vector>

using std::vector;

class MemPool {
public:
    explicit MemPool(int num);
    void* allocate(size_t size);
    void deallocate(void* ptr, size_t size);
    MemPool(const MemPool&) = delete;
    void operator=(const MemPool&) = delete;
private:
    vector<ManageChunk> mem;
    vector<Mutex> mutex;
    int num;
};


#endif //MEMPOOL_MEMPOOL_H
