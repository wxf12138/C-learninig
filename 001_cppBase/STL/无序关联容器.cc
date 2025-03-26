/*
    一、 标准容器
    1. 顺序容器
    vector
    deque
    list
    2. 容器适配器
    stack
    queue
    priority_queue
    3. 关联容器
    无序关联容器 -》 链式哈希表 增删查 O(1)
    set: 集合 key  map： 映射表 key-value
    unordered_set 单重集合
    unordered_map 单重映射表
    undored_multiset 多重集合
    unordered_multimap 多重映射表

    有序关联容器 -》 二叉树（红黑树） 增删查 O(log2N)
    set
    multiset
    map
    multimap
 */

#include <iostream>
#include <vector>
#include <unordered_map>
// 使用有序关联容器包含的头文件
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>
// 使用无需关联容器包含的头文件
#include <unordered_set>
#include <unordered_map>
#include <deque>
using namespace std;
/* 
     关联容器：
     1. 各个容器底层的数据结构 O(1) O(logN)
     2. 常用增删查方法
     增加： insert（val）
     遍历： iterator自己搜索，调用find成员方法
     删除： erase(val) erase(iterator)
 */

 int main()
 {
    #if 0
    unordered_multiset<int> set1; //不会存储key值重复的元素
    for (int i = 0; i < 50; i++)
    {
        set1.insert(rand() % 20 + 1);
    }
   
    auto it = set1.begin();
    while (it != set1.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;

    set1.erase(18);
    for (auto it = set1.begin(); it != set1.end();)
    {
       if (*it == 16)
       {
            it = set1.erase(it);        
       }
       else
       {
        ++it;
       }
    }
    
    it = set1.find(20);//find(20) 返回第一个匹配的迭代器，erase(it) 仅删除该迭代器指向的元素。如果存在多个 20，其他实例会保留。

    if (it != set1.end())
    {
        set1.erase(it);
    }

    for (int v : set1)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
    #endif
    /* 
        [key, value]
        map的operator[]
        1. 查询
        2. 如果key不存在， 他会插入一堆数据
    */
    // map<int, string> map1;
    // map1.insert(make_pair(1, "hello"));
    // map1.insert({2, "world"});

    // //map1.erase(1);
    // map1[3] = "nihao";

    // auto it1 = map1.find(3);
    // if (it1 != map1.end())
    // {
    //     cout << it1->first << " " << it1->second << endl;
    // }

   // cout << map1.size() << endl;
    //cout << map1[3] << endl;

    // 处理海量数据查重复；去重复的时候
    // const int N = 100;
    // int array[N] = {0};
    // for (int i = 0; i < N; i++)
    // {
    //     array[i] = rand() % N+1;
    // }

    //查重
    #if 0
    unordered_map<int, int> map1;
    for(int k : array)
    {
        auto it = map1.find(k);
        if(it == map1.end())
        {
            map1.insert(make_pair(k, 1));
        }
        else
        {
            it->second++;
        }
    }

    for (pair<int, int> p : map1)
    {
        if (p.second > 1){
            cout << p.first << " " << p.second << endl;
        }
    }
    #endif
    //去重
    #if 0
    unordered_set<int> set;
    for (int v : array)
    {
        set.insert(v);
    }

    for (int v : set)
    {
        cout << v << " ";
    }
    cout << endl;
    #endif
    return 0;
}