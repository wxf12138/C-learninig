#include <iostream>
#include <vector>
#include <queue>
#include <functional>

/*
海量数据求top k问题
1. 求最大/最小的前k个元素 答：堆（优先级队列）
2. 求最大/最小的第k个元素 答：快排分割，能够在log2n时间内，把小于基准数调整到左边，大于基准数的数调整到右边。
基准数（index）就可以认为是第（index+1）小的整数。[0, index]就是前idex+1小的元素。

10000个整数，找值前10大的元素
先用前10个整数创建一个小根堆(最小值就在堆顶)然后遍历剩下的整数，
如果整数比堆顶元素大，那么删除堆顶元素(出堆)，然后再把整数入堆，
遍历完所有整数，小根堆里面放的就是值最大的前10个元素了。
*/

// 快排分割
int partition(std::vector<int> &arr, int i, int j)
{
    int k = arr[i];
    while (i < j)
    {
        while (i < j && arr[j] >= k)
            j--;
        if (i < j)
            arr[i++] = arr[j];

        while (i < j && arr[i] < k)
            i++;
        if (i < j)
            arr[j--] = arr[i];
    }
    arr[i] = k;
    return i;
}

int selectNok(std::vector<int> &arr, int i, int j, int k)
{
    int pos = partition(arr, i, j); // 返回第一次交换的值
    if (pos == k - 1)
        return pos;
    else if (pos > k - 1)
        return selectNok(arr, i, pos - 1, k);
    else
        return selectNok(arr, pos + 1, j, k);
}

int main()
{

#if 0
    std::vector<int> vec;
    for (int i = 0; i < 10000; i++)
    {
        vec.push_back(rand() % 100 + 1);
    }
    auto it = vec.begin();
    for (; it != vec.end();)
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;

    std::priority_queue<int, std::vector<int>, std::greater<int>> minheap;

    // 先用前10个整数创建一个小根堆(最小值就在堆顶)
    int k = 10;
    for (int i = 0; i < k; i++)
    {
        minheap.push(vec[i]);
    }
    // 然后遍历剩下的整数
    for (; k < vec.size(); k++)
    {
        if (vec[k] > minheap.top())
        {
            minheap.pop();
            minheap.push(vec[k]);
        }
    }
    // 遍历完所有整数，小根堆里面放的就是值最大的前10个元素了。
    while (!minheap.empty())
    {
        std::cout << minheap.top() << " ";
        minheap.pop();
    }
    std::cout << std::endl;
#endif

    std::vector<int> vec;
    for (int i = 0; i < 100; i++)
    {
        vec.push_back(rand() % 100 + 1);
    }
    auto it = vec.begin();
    for (; it != vec.end();)
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;

    int pos = selectNok(vec, 0, vec.size() - 1, 10);
    std::cout << "pos: " << vec[pos] << std::endl;

    
    //传统排序
    std::priority_queue<int, std::vector<int>, std::less<int>> queue;

    for (int i = 0; i < 100; i++)
    {
        queue.push(vec[i]);
    }

    while (!queue.empty())
    {
        std::cout << queue.top() << " ";
        queue.pop();
    }
    std::cout << std::endl;
}
