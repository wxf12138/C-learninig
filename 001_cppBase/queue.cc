#include <queue>
#include <iostream>
#include <cstdlib>
class Queue
{
public:
    Queue(int size = 1)
    {
        _pQue = new int[size];
        _front = _rear = 0;
        _size = size;
    }

    Queue(const Queue &src)
    {
        _size = src._size;
        _front = src._front;
        _rear = src._rear;
        _pQue = new int[_size];
        for (int i = _front; i != _rear; (i + 1) % _size)
        {
            _pQue[i] = src._pQue[i];
        }
    }

    Queue &operator=(const Queue &src)
    {
        if (this == &src)
            return *this;
        delete src._pQue;
        _size = src._size;
        _front = src._front;
        _rear = src._rear;
        _pQue = new int[_size];
        for (int i = _front; i != _rear; (i + 1) % _size)
        {
            _pQue[i] = src._pQue[i];
        }
        return *this;
    }

    ~Queue()
    {
        delete[] _pQue;
        _pQue = nullptr;
    }
    void addQue(int val)
    {
        if(full())
            resize();
        _pQue[_rear] = val;
        _rear = (_rear + 1) % _size;
    }
    int front()
    {
        if (empty())
            return 0;       
        return _pQue[_front];
    }
    int top()
    {
        _front = (_front + 1) % _size;
        return _pQue[_front];
    }
    bool full() { return (_rear + 1) % _size == _front; }
    bool empty() { return _front == _rear; }
    void resize()
    {
        int *ptmp = new int[_size * 2];
        int index = 0;
        for (int i = _front; i != _rear; i = (i + 1) % _size)
        {
            ptmp[index++] = _pQue[i];
        }
        delete[] _pQue;
        _pQue = ptmp;
        _front = 0;
        _rear = index;
        _size *= 2;
    }

public:
    int *_pQue; // 申请队列空间地址
    int _front;
    int _rear;
    int _size;
};

int main()
{
    Queue q;
    for (int i = 0; i < 9; i++)
    {
        q.addQue(rand() % 100 + 1);
    }

    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.top();
    }
    std::cout << std::endl;
    std::cout << q._size<< std::endl;
}