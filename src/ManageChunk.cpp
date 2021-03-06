//
// Created by ltc on 2021/3/6.
//

#include "ManageChunk.h"
#include <stdexcept>

ManageChunk::ManageChunk(int num, size_t size):num(num), size(size), head(new MemChunk(0, 0)), free(nullptr){}

void* ManageChunk::allocate() {
    if (head->next == nullptr) {
        head->next = new MemChunk(num, size);
        return head->next->allocate();
    }
    MemChunk* curr = head;
    while (curr->next != nullptr){
        if (curr->next->num != 0){
            if (curr == free){
                free = nullptr;
            }
            if (curr == head){
                return curr->next->allocate();
            }
            MemChunk* alloc = curr->next;
            curr->next = curr->next->next;
            alloc->next = head->next;
            head->next = alloc;
            return alloc->allocate();
        }
        curr = curr->next;
    }
    MemChunk* alloc = new MemChunk(num, size);
    alloc->next = head->next;
    head->next = alloc;
    return alloc->allocate();
}

void ManageChunk::deallocate(void* ptr) {
    if (ptr != nullptr){
        MemChunk* curr = head;
        while (curr->next != nullptr){
            if (ptr >= (void*)(curr->next->start) && ptr < (void*)((char*)(curr->next->start)+size*num)){
                curr->next->deallocate(ptr);
                if (curr->next->num == num){
                    if (free != nullptr && free != curr){
                        MemChunk* dealloc = free->next;
                        free->next = free->next->next;
                        dealloc->next = nullptr;
                        delete dealloc;
                    }
                }
                if (curr == head){
                    return;
                }
                MemChunk* alloc = curr->next;
                curr->next = curr->next->next;
                alloc->next = head->next;
                head->next = alloc;
                free = head;
                return;
            }
            curr = curr->next;
        }
        throw std::logic_error("内存释放错误");
    }
}

ManageChunk::~ManageChunk() {
    head = head->next;
    while (head != nullptr){
        MemChunk* temp = head;
        head = head->next;
        delete temp;
    }
}
