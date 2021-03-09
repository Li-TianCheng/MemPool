//
// Created by ltc on 2021/3/6.
//

#ifndef MEMPOOL_MANAGECHUNK_H
#define MEMPOOL_MANAGECHUNK_H

#include "MemChunk.h"

class ManageChunk {
public:
    explicit ManageChunk(size_t size);
    void* allocate(int num);
    void deallocate(void* ptr, int num);
    ~ManageChunk();
private:
    MemChunk* head;
    MemChunk* free;
    size_t size;
};


#endif //MEMPOOL_MANAGECHUNK_H
