//
// Created by ltc on 2021/3/7.
//

#include "Mutex.h"
#include <stdexcept>

Mutex::Mutex() {
    if (pthread_mutex_init(&mutex, nullptr) != 0){
        throw std::runtime_error("互斥锁创建错误");
    }
}

void Mutex::lock() {
    if (pthread_mutex_lock(&mutex) != 0){
        throw std::runtime_error("互斥锁加锁错误");
    }
}

void Mutex::unlock() {
    if (pthread_mutex_unlock(&mutex) != 0){
        throw std::runtime_error("互斥锁释放锁错误");
    }
}

bool Mutex::tryLock() {
    int state = pthread_mutex_trylock(&mutex);
    if (state == EBUSY) {
        return false;
    }
    if (state != 0){
        throw std::runtime_error("互斥锁尝试错误");
    }
    return true;
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&mutex);
}