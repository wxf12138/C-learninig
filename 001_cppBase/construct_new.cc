#include <iostream>
using namespace std;
template <typename T>
class Queue
{
public:
    Queue() : _front(nullptr), _rear(nullptr)
    {
        _front = _rear = new QueueItem();
    }
    void push(const T &val)
    {
        _rear->_next = new QueueItem(val);
        _rear = _rear->_next;
    }
    void pop()
    {
        if (empty())
            return;
        QueueItem *first = _front->_next;
        _front->_next = first->_next;
        if (_front->_next == nullptr)
            _rear = _front;
        delete first;
    }
    T front() const
    {
        return _front->_next->_data;
    }
    bool empty() const
    {
        return _front == _rear;
    }
    ~Queue()
    {
        QueueItem *cur = _front;
        while (cur != nullptr)
        {
            _front = cur->_next;
            delete cur;
            cur = _front;
        }
    }

private:
    struct QueueItem
    {
        QueueItem(T data = T()) : _data(data), _next(nullptr) {}
        // 给QueueItem提供自定义内存管理
       void* operator new (size_t size)
        {
            if (_pool == nullptr)
            {
                _pool = (QueueItem*)new char [POOL_SIZE*sizeof(QueueItem)];
                QueueItem *cur = _pool;
                for (; cur < _pool + POOL_SIZE-1; ++cur)
                {
                    cur->_next = cur + 1;
                }
                cur->_next = nullptr;
            }
            //如果对象池不等于空，则从对象池中取一个出来
            QueueItem* p = _pool;
			_pool = _pool->_next;
			return p;
        }
        void operator delete(void *p)
        {
            QueueItem *q = (QueueItem *)p;
            q->_next = _pool;
            _pool = q;
        }
        T _data;
        QueueItem *_next;
        static QueueItem *_pool;
        static const int POOL_SIZE = 10;
    };
    T _data;
    QueueItem *_front;
    QueueItem *_rear;
};

template <typename T>
//在模板类中，当引用嵌套的依赖类型（如 `Queue<T>::QueueItem`）时，必须使用 `typename` 明确告知编译器这是一个类型（而非静态成员或变量）。
typename Queue<T>::QueueItem* Queue<T>::QueueItem::_pool = nullptr;

int main()
{
    Queue<int> q;
    for (int i = 0; i < 10; ++i)
    {
        q.push(i);
        q.pop();
    }
    cout << q.empty() << endl;
    return 0;
}