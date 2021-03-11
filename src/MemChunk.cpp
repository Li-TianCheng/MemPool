//
// Created by ltc on 2021/3/6.
//

#include "MemChunk.h"
#include <malloc.h>
#include <new>

MemChunk::MemChunk(int num, size_t size):num(num), free(nullptr), start(nullptr), prev(nullptr), next(nullptr){
    while (true){
        free = (obj*)malloc(num * size);
        if (free != nullptr){
            break;
        }else{
            throw std::bad_alloc();
        }
    }
    start = free;
    for (int i = 0; i < num-1; i++){
        free->next = (obj*)((char*)free+size);
        free = free->next;
    }
    free->next = nullptr;
    free = start;
};

void* MemChunk::allocate() {
    obj* curr = free;
    free = free->next;
    num--;
    return curr;
}

void MemChunk::deallocate(void *ptr) {
    ((obj*)ptr)->next = free;
    free = (obj*)ptr;
    num++;
}

MemChunk::~MemChunk() {
    ::free(start);
}