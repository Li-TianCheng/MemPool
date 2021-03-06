#include <iostream>
#include "MemPool.h"
#include "MemPoolAllocator.h"
#include <ctime>
#include <unordered_set>

using namespace std;

MemPool memPool(1000);
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
    long long n = 100000000;
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
    unordered_set<int> set;
    for (int i = 0; i < 10*n; i++){
        set.insert(random()%n);
    }
    A* p[n];
    start = clock();
    for (int i : set){
        p[i] = new A;
    }
    cout << (double)(clock()-start) / CLOCKS_PER_SEC << " ";
    start = clock();
    for (int i: set){
        delete p[i];
    }
    cout << (double)(clock()-start) / CLOCKS_PER_SEC << endl;

    B* q[n];
    start = clock();
    for (int i : set){
        q[i] = new B;
    }
    cout << (double)(clock()-start) / CLOCKS_PER_SEC << " ";
    start = clock();
    for (int i : set){
        delete q[i];
    }
    cout << (double)(clock()-start) / CLOCKS_PER_SEC << endl;
    return 0;
}
