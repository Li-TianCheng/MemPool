#include <iostream>
#include "MemPool.h"
#include "MemPoolAllocator.h"
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

MemPool memPool(100000);
class A{
public:
    static void* operator new(size_t size){
        return memPool.allocate(size);
    }
    static void operator delete(void* ptr, size_t size){
        memPool.deallocate(ptr, size);
    }
private:
    double a, b, c, d, e, f, g, h, i, j, k;
};

class B{
private:
    double a, b, c, d, e, f, g, h, i, j, k;
};

int main() {
    vector<B, MemPoolAllocator<B, 10000>> v;
    long long n = 10000000;
    clock_t start = clock();
    for (int i = 0; i < n; i++) {
        v.emplace_back();
    }
    for (int i = 0; i < n; i++) {
        v.pop_back();
    }
    for (int i = 0; i < n; i++) {
        v.emplace_back();
    }
    cout << (double)(clock()-start) / CLOCKS_PER_SEC << endl;
    vector<B, std::allocator<B>> u;
    start = clock();
    for (int i = 0; i < n; i++) {
        u.emplace_back();
    }
    for (int i = 0; i < n; i++) {
        u.pop_back();
    }
    for (int i = 0; i < n; i++) {
        u.emplace_back();
    }
    cout << (double)(clock()-start) / CLOCKS_PER_SEC << endl;

    n = 100000;
    vector<int> index(n);
    for (int i = 0; i < n; i++){
            index[i] = i;
    }
    shuffle(index.begin(), index.end(), std::mt19937(std::random_device()()));
    A* p[n];
    start = clock();
    for (int i : index){
        p[i] = new A;
    }
    cout << (double)(clock()-start) / CLOCKS_PER_SEC << " ";
    start = clock();
    for (int i = 0; i < n; i++){
        delete p[i];
    }
    cout << (double)(clock()-start) / CLOCKS_PER_SEC << endl;

    B* q[n];
    start = clock();
    for (int i : index){
        q[i] = new B;
    }
    cout << (double)(clock()-start) / CLOCKS_PER_SEC << " ";
    start = clock();
    for (int i = 0; i < n; i++){
        delete q[i];
    }
    cout << (double)(clock()-start) / CLOCKS_PER_SEC << endl;
    return 0;
}
