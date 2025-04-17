#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

// 单向循环链表
class CircleLink
{
public:
    CircleLink()
    {
        head_ = new Node();
        tail_ = head_;
        head_->next_ = head_;
    }
    ~CircleLink()
    {
        Node *p = head_->next_;
        while (p != head_)
        {
            head_->next_ = p->next_;
            delete p;
            p = head_->next_;
        }
        delete head_;
    }

public:
    void InsterTail(int val)
    {
        Node *node = new Node(val);

        node->next_ = head_;
        tail_->next_ = node;
        tail_ = node; // 更新尾节点
    }

    void InsterHead(int val)
    {
        Node *node = new Node(val);

        node->next_ = head_->next_;
        head_->next_ = node;
        if (node->next_ = head_)
        {
            tail_ = node;
        }
    }

    void RemoveAll(int val)
    {
        Node *q = head_;
        Node *p = head_->next_; // 要删除的节点
        while (p != head_)
        {
            if (p->data_ == val)
            {
                if (p == tail_)
                {
                    tail_ = q;
                }
                q->next_ = p->next_; // 跳过p
                delete p;
                p = q->next_;
            }
            q = q->next_;
            p = p->next_;
        }
    }

    void Remove(int val)
    {
        Node *q = head_;
        Node *p = head_->next_; // 要删除的节点
        while (p != head_)
        {
            if (p->data_ == val)
            {
                if (p == tail_)
                {
                    tail_ = q;
                }
                q->next_ = p->next_; // 跳过p
                delete p;
                return;
            }
            q = q->next_;
            p = p->next_;
        }
    }

    bool Find(int val) const
    {
        Node *current = head_->next_; // 从头结点的下一个节点开始遍历 避免直接操作head节点
        while (current != head_)
        {
            if (current->data_ == val)
            {
                return true;
            }
            current = current->next_;
        }
        return false;
    }

    void print() const
    {
        if (head_ == nullptr || head_->next_ == head_)
        {
            cout << "List is empty." << endl;
            return;
        }

        Node *p = head_->next_; // 从第一个有效节点开始（跳过头节点）

        while (p != head_)
        {
            cout << p->data_ << " ";
            p = p->next_;
        }

        cout << endl;
    }

private:
    struct Node
    {
        Node(int data = 0) : data_(data), next_(nullptr) {}
        int data_;
        Node *next_;
    };

    Node *head_;
    Node *tail_;
};

int main()
{
    CircleLink clink;
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        clink.InsterTail(rand() % 100);
    }

    clink.InsterTail(100);
    clink.print();
    cout << clink.Find(100) << endl;
    clink.Remove(100);
    clink.print();
}