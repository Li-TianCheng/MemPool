//
// Created by ltc on 2021/3/6.
//

#ifndef MEMPOOL_MEMPOOLALLOCATOR_H
#define MEMPOOL_MEMPOOLALLOCATOR_H

#include <cstddef>
#include "MemPool.h"

using std::allocator;

template<typename T, int num>
class MemPoolAllocator {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T* const_pointer;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef unsigned char data_type;
    typedef unsigned char* data_pointer;
    template<typename U>
    struct rebind{
        typedef MemPoolAllocator<U, num> other;
    };
    MemPoolAllocator() noexcept;
    pointer allocate(size_t n, const_pointer hint = nullptr);
    void deallocate(pointer p, size_t n);
private:
    MemPool allocator;
};

template<typename T, int num> inline
MemPoolAllocator<T, num>::MemPoolAllocator() noexcept : allocator(num){}

template<typename T, int num> inline
T* MemPoolAllocator<T, num>::allocate(size_t n, const_pointer) {
    return (pointer)allocator.allocate(sizeof(T)*n);
}

template<typename T, int num> inline
void MemPoolAllocator<T, num>::deallocate(T* p, size_t n){
    allocator.deallocate((void*)(p), sizeof(T)*n);
}


#endif //MEMPOOL_MEMPOOLALLOCATOR_H
