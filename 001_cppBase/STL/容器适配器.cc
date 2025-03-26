#include <list>
#include <queue>
#include <stack>    
#include <iostream>
using namespace std;

/* 
    标准容器 - 容器适配器 -》 设计模式，就叫做适配器模式
    怎么理解适配器？
    1 适配器底层没有自己的数据结构，他是另外一个容器的封装， 他的方法全部由底层依赖的容器实现
    2 没有实现自己的迭代器

    template<typename T, typename Container = deque<T>>
    class Stack
    {
        public:
            void push(const T& x)
            {
                c.push_back(x);
            }
        private:
            Container c;    //底层的一个容器
    };
*/


int main()
{
    // stack<int> s1;
    // for (int i = 0; i < 20; i++)
    // {
    //     s1.push(rand() % 100 + 1);
    // }

    // cout<< "s1.size() = " << s1.size() << endl;

    // while (!s1.empty())
    // {
    //     cout << s1.top() << " ";
    //     s1.pop();
    // }

    // queue<int> q1;
    // for (int i = 0; i < 20; i++)
    // {
    //     q1.push(rand() % 100 + 1);
    // }
    // cout << "q1.size() = " << q1.size() << endl;
    // while (!q1.empty())
    // {
    //     cout << q1.front() << " " ;
    //     q1.pop();
    // }
    // cout << endl;

    priority_queue<int> pq1;
    for (int i = 0; i < 20; i++)
    {
        pq1.push(rand() % 100 + 1);
    }
    cout << "pq1.size() = " << pq1.size() << endl;

    while (!pq1.empty())
    {
        cout << pq1.top() << " ";
        pq1.pop();
    }
    
    return 0;
}