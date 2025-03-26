#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main()
{//在 C++标准库中，priority_queue（优先队列）的默认行为是大根堆（最大元素优先出队）。
   using Minheap = priority_queue<int, vector<int>,  greater<int>>;
    Minheap que;
    for (int i = 0; i < 10; ++i)
    {
        que.push(rand() % 100);  
    }

    while (!que.empty())
    {
        cout << que.top() << " ";
        que.pop();
    }
    cout << endl;  
}