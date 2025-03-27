#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;

/*
    题目： 求数据的重复次数最大/小 的前/第 k个

    答： 哈希统计 + 堆/快排
*/

// 快排
int partition(vector<pair<int, int>> &map, int left, int right)
{
    auto rmap = map[left];
    int k = map[left].second;
    while (left < right)
    {
        while (left < right && map[right].second >= k)
        {
            right--;
        }
        if (left < right)
        {
            map[left] = map[right];
            left++;
        }
        while (left < right && map[left].second < k)
        {
            left++;
        }
        if (left < right)
        {
            map[right] = map[left];
            right--;
        }
    }
    map[left] = rmap;
    return left;
}

int select(vector<pair<int, int>> &map, int left, int right, int k)
{
    int pos = partition(map, left, right);
    if (pos == k - 1)
    {
        return map[pos].second;
    }
    else if (pos > k - 1)
    {
        return select(map, left, pos - 1, k);
    }
    else
    {
        return select(map, pos + 1, right, k);
    }
}
int main()
{
    vector<int> vec;
    for (int i = 0; i < 100; i++)
    {
        vec.push_back(rand() % 10);
    }

    // 统计所有数据的重复次数
    unordered_map<int, int> map;
    for (int val : vec)
    {
        map[val]++;
    }
    // 根堆解法

    // 先定义一个小根堆 数字和重复的次数
    using P = pair<int, int>;
    using FUNC = function<bool(P &, P &)>;
    using MinHeap = priority_queue<P, vector<P>, FUNC>;
    MinHeap minHeap([](auto &a, auto &b) -> bool
                    { return a.second > b.second; });

    // 先放入k个元素
    int k = 0;
    auto it = map.begin();

    // 先从表中读10个数据到小根堆，建立topk的小根堆，最小的元素在堆顶
    //堆中始终保持了 k 个最大的元素（整个数组中最大的 k 个数字）。
    //而在这 k 个数字中，堆顶（小根堆的最小元素）就是这 k 个元素中最小的，
    //也就是说，它在整个数组中恰好是第 k 大的元素。
    for (; it != map.end() && k < 10; it++, k++)
    {
        minHeap.push(*it);
    }

    // 把K + 1到末尾的元素进行遍历，和对顶元素进行比较
    for (; it != map.end(); it++)
    {
        if (it->second > minHeap.top().second)
        {
            minHeap.pop();
            minHeap.push(*it);
        }
    }

    // 最大的第k个元素
    cout << "第 " << k << " 大的重复次数是: " << minHeap.top().second << endl;

    // 堆出剩下堆中的重复次数最大的前k个
    while (!minHeap.empty())
    {
        cout << minHeap.top().first << ":" << minHeap.top().second << endl;
        minHeap.pop();
    }
    cout << "=======================================================================" << endl;
    // 将 unordered_map 转换为 vector<pair<int, int>>
    vector<pair<int, int>> freq_vec(map.begin(), map.end());

    // 快排解法
    int n = freq_vec.size();

    // 0 -- size-1 排序为升序排列，第 n-k+1 小，即第 k 大;
    int pos = select(freq_vec, 0, n -1 , n - 10 + 1);
    cout << "第 " << 10 << " 大的重复次数是: " << pos << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << freq_vec[i].first << ":" << freq_vec[i].second << endl;
    }
}