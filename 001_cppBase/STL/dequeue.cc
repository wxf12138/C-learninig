#include <iostream>
#include <deque>
#include <vector>
#include <list>
using namespace std;

/*
    底层数据结构：动态开辟的二维数组，一维数组从2开始，以2倍的方式进行扩容，每次扩容后，原来第二维的数组，从新的一维的数组下标oldsize/2
    开始存放，上下预留相同空间，方便元素首位添加

    deque<int> deq;
    增加：
    deq.pushback(20), 从末尾添加元素 O(1)
    deq.pushfront(20), 从首位添加元素 O(1) vec.insert(vec.begin(),20) O(n)
    deq.insert(it, 20), it指向的位置添加元素 O(n)
    删除：
    deq.popback(), 从末尾删除 O(1)
    deq.popfront(), 从首位删除 O(1)
    deq.erase(it, 20), it指向位置删除元素 O(n)
    查询搜索：
    iterator(insert, erase要考虑迭代器失效问题)

    内存并不连续
 */

 /* 
    list：
    底层数据结构是：双向循环链表
    list<int> mylist;
    增加：
    mylist.pushback(20), 从末尾添加元素 O(1)
    mylist.pushfront(20), 从首位添加元素 O(1) vec.insert(vec.begin(),20) O(n)
    mylist.insert(it, 20), it指向的位置添加元素 O(1) 链表进行插入操作时，先查询，对于链表来说，查询效率慢
    删除：
    mylist.popback(), 从末尾删除 O(1)
    mylist.popfront(), 从首位删除 O(1)
    mylist.erase(it, 20), it指向位置删除元素 O(1)
  */

/* 
    vector: 动态数组，内存是连续的，2倍的方式进行扩容
*/