//
// Created by ltc on 2021/3/6.
//

#ifndef MEMPOOL_MANAGECHUNK_H
#define MEMPOOL_MANAGECHUNK_H

#include "MemChunk.h"

class ManageChunk {
public:
    ManageChunk(int num, size_t size);
    void* allocate();
    void deallocate(void* ptr);
    ~ManageChunk();
private:
    MemChunk* head;
    MemChunk* free;
    int num;
    size_t size;
};


#endif //MEMPOOL_MANAGECHUNK_H
