#include <iostream>
using namespace std;

#if 0
class Queue
{
public:
    Queue(int size = 10)
        : front_(0), rear_(0), cap_(size), size_(0)
    {
        pQue_ = new int[cap_];
    }
    ~Queue()
    {
        delete[] pQue_;
        pQue_ = nullptr;
    }

public:
    void push(int val)
    {
        if ((rear_ + 1) % cap_ == front_)
        {
            expand(cap_ * 2);
        }
        pQue_[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
        size_++;
    }

    void pop()
    {
        if (front_ == rear_)
            throw "queue is empty";
        front_ = (front_ + 1) % cap_;
        size_--;
    }

    int front() const
    {
        if (front_ == rear_)
            throw "queue is empty";
        return pQue_[front_];
    }

    int rear() const
    {
        if (front_ == rear_)
            throw "queue is empty";
        return pQue_[(rear_ - 1 + cap_) % cap_];
    }

    bool empty() const
    {
        return front_ == rear_;
    }

    int size()
    {
        return size_;
    }

private:
    void expand(int size)
    {
        int *p = new int[size];
        int i = 0;
        int j = front_;
        for (; j != rear_; j = (j + 1) % cap_)
        {
            p[i] = pQue_[j];
            i++;
        }
        delete[] pQue_;
        pQue_ = p;
        cap_ = size;
        front_ = 0;
        rear_ = i;
    }

private:
    int front_;
    int rear_;
    int *pQue_;
    int cap_;
    int size_;
};
#endif

// 链式队列
class Queue
{
public:
    Queue()
    {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }
    ~Queue()
    {
        if (head_ == nullptr)
            return;

        Node *p = head_->next_;
        while (p != head_)
        {
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;
            p = head_->next_;
        }
        delete head_; // 最后别忘了删掉头节点
        head_ = nullptr;
    }
public:
    void push(int val)
    {
        Node* p = head_->pre_; //指向末尾节点
        Node* node = new Node(val);
        node->next_ = head_;
        node->pre_ = p;
        p->next_ = node;
        head_->pre_ = node;
    }

    void pop()
    {
        Node* p = head_->next_;
        head_->next_ = p->next_;
        p->next_->pre_ = head_;
        delete p;
    }

    int front()
    {
        if(head_->next_ == head_)
            throw "queue is empty";
        return head_->next_->data_;
    }
    int rear()
    {
        if(head_->next_ == head_)
            throw "queue is empty";
        return head_->pre_->data_;
    }

    bool empty()
    {
        return head_->next_ == head_;
    }
private:
    struct Node
    {
        Node(int data = 0)
            : data_(data), next_(nullptr), pre_(nullptr)
        {
        }
        int data_;
        Node *next_;
        Node *pre_;
    };
    Node *head_;
};

int main()
{
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    Queue que;

    for (int v : arr)
    {
        que.push(v);
    }

    cout << que.front() << endl;
    cout << que.rear() << endl;

    que.push(100);
    que.push(200);
    que.push(300);
    cout << que.front() << endl;
    cout << que.rear() << endl;

    while (!que.empty())
    {
        cout << que.front() << " " << que.rear() << endl;
        que.pop();
    }
}