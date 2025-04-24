#include <iostream>
#include <functional>
#include <string.h>
using namespace std;

class PriorityQueue
{
public:
    using Comp = function<bool(int, int)>;
    PriorityQueue(int cap = 20, Comp comp = greater<int>())
    : size_(0)
    , cap_(cap)
    , comp_(comp)
    {
        que_ = new int[cap_];
    }

    PriorityQueue(Comp comp)
    : size_(0)
    , cap_(20)
    , comp_(comp)
    {
        que_ = new int[cap_];
    }


    ~PriorityQueue()
    {
        delete[] que_;
        que_ = nullptr;
    }

    void push(int val)
    {
        if (size_ == cap_)
        {
            int* p = new int[2 * cap_];
            memcpy(p, que_, cap_*sizeof(int));
            delete[] que_;
            que_ = p;
            cap_ *= 2;
        }
        if (size_ == 0)
        {
            que_[size_] = val;
        }
        else
        {
            // 堆里面有多个元素，需要进行上浮
            siftup(size_, val);
        }
        size_++;
    }

    void pop()
    {
        if (size_ == 0)
            throw "queue is empty";
        size_--;
        if (size_ > 0)
        {
            // 删除堆顶元素， 要进行下沉
            siftdown(0, que_[size_]); //que_[size_] 为出堆后的最后一个元素
        }
    }
    bool empty() const { return size_ == 0;}

    int top() const { return que_[0];}

    int size() const { return size_;}

private:
    // 入堆上浮调整
    void siftup(int size, int val)
    {
        while (size > 0) // 最多计算到根节点（0号位）
        {
            int father = (size - 1) / 2;
            if (comp_(val, que_[father])) 
            {
                que_[size] = que_[father];
                size = father;
            }
            else
            {
                break;
            }
        }
        que_[size] = val;
    }

    // 出堆要下沉调整
    void siftdown(int i, int val)
    {
        // 下沉到最后一个非叶子节点
        while(i < size_ / 2)
        {
            int child = i * 2 + 1;
            if (child + 1 < size_ && comp_(que_[child + 1], que_[child]))            
            {
                child = child + 1;
            }

            if (comp_(que_[child], val))
            {
                que_[i] = que_[child];
                i = child;
            }
            else
            {
                break;
            }
        }
        que_[i] = val;  
    }




private:
    int* que_;
    int size_;
    int cap_;
    Comp comp_;
};

int main()
{
    PriorityQueue queue([] (int a, int b) { return a < b;});
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        queue.push(rand() % 100);
    }

    while (!queue.empty())
    {
        cout << queue.top() <<" ";
        queue.pop();
    }
    cout << endl;
}