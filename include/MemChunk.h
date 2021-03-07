//
// Created by ltc on 2021/3/6.
//

#ifndef MEMPOOL_MEMCHUNK_H
#define MEMPOOL_MEMCHUNK_H

#include <cstddef>

class MemChunk {
public:
    MemChunk(int num, size_t size);
    void* allocate();
    void deallocate(void* ptr);
    ~MemChunk();
private:
    friend class ManageChunk;
    struct obj{
        obj* next;
    };
    obj* free;
    obj* start;
    MemChunk* prev;
    MemChunk* next;
    int num;
};


#endif //MEMPOOL_MEMCHUNK_H
