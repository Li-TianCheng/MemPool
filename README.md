# MemPool
c++高性能内存池

## c++高性能内存池
1.可直接初始化MemPool，并修改class中operate new和operate delete来修改class分配方式

2.可设置stl容器分配器为MemPoolAllocator来修改stl容器内存分配方式

3.内存池可自动对过多内存进行回收

## 结构图
![image](https://github.com/Li-TianCheng/MemPool/blob/main/MemPool%E7%BB%93%E6%9E%84.png)