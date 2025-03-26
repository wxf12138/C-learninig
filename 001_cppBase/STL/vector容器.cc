#include <iostream>
#include <vector>
using namespace std;

/* vector : 向量容器
    底层数据结构：动态开辟的数组，每次以原来空间大小的2倍进行扩容。
    增加：
    vec.push_back(2): 末尾添加元素O(1)，可能导致容器扩容
    vec.insert(it,20): 在指定位置添加一个元素2 O(n)
    删除
    vec.pop_back(): 删除末尾元素O(1)
    vec.erase(it): 删除指定位置的元素O(n)
    查询
    operator[]: 通过下标访问元素O(1)
    iterator: 通过迭代器访问元素O(1)
    find,for_each
    foreach -> 通过迭代器实现

    注意：对容器进行连续的插入或者删除操作时。一定要更新迭代器，否则迭代器会失效。
    常用方法介绍：
    size(): 返回容器中元素的个数
    empty(): 判断容器是否为空
    clear(): 清空容器
    reserve(): 容器预留空间，减少扩容次数
    resize(): 容器大小调整
    swap(): 交换两个容器
 */

 int main() {
    vector<int> v;
    //v.reserve(100); //只给容器底层开辟一个指定大小的内存空间
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(rand() % 100+1);
    }
    v.resize(20);

#if 0
    int size = v.size();
    for (int i = 0; i < size; ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    // 把vec中的所有偶数删除
    for (auto it = v.begin(); it != v.end();)
    {
        if (*it % 2 == 0)
        {
            it = v.erase(it);
        }
        else
        {
            ++it;
        }
    }
    

    auto it1 = v.begin();
    while (it1 != v.end())
    {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;

    //给vec中所有的奇数前面都添加一个小于当前奇数1的偶数
    auto it = v.begin();
    while ( it != v.end())
    {
        if (*it % 2 != 0)
        {
            it = v.insert(it, *it - 1);
            ++it;
        }
        ++it;      
    }
    auto it2 = v.begin();
    while (it2 != v.end())
    {
        cout << *it2 << " ";
        ++it2;
    }
    cout << endl;
#endif
    for (auto i : v)
    {
        cout << i << " ";
    }

    return 0;
}