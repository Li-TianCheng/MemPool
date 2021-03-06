//
// Created by ltc on 2021/3/6.
//

#include "MemChunk.h"
#include <malloc.h>
#include <new>

MemChunk::MemChunk(int num, size_t size):num(num), freePointer(nullptr), start(nullptr), next(nullptr){
    if (num*size == 0){
        return;
    }
    while (true){
        freePointer = (obj*)malloc(num * size);
        if (freePointer != nullptr){
            break;
        }else{
            throw std::bad_alloc();
        }
    }
    start = freePointer;
    for (int i = 0; i < num-1; i++){
        freePointer->next = (obj*)((char*)freePointer+size);
        freePointer = freePointer->next;
    }
    freePointer->next = nullptr;
    freePointer = start;
};

void* MemChunk::allocate() {
    obj* curr;
    curr = freePointer;
    freePointer = freePointer->next;
    num--;
    return curr;
}

void MemChunk::deallocate(void *ptr) {
    ((obj*)ptr)->next = freePointer;
    freePointer = (obj*)ptr;
    num++;
}

MemChunk::~MemChunk() {
    delete start;
}