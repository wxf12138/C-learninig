#include <iostream>
using namespace std;

// 节点类型
struct Node
{
    Node(int data = 0) : data_(data), next_(nullptr) {}
    int data_;
    Node *next_;
};
class Clink
{
public:
    Clink()
    {
        head_ = new Node(); // 头结点
    }
    ~Clink()
    {
        while (head_ != nullptr)
        {
            Node *p = head_->next_;
            delete head_;
            head_ = p;
        }
    }

    void insertTail(int data)
    {
        Node *p = head_;
        // 找到当前链表末尾节点
        while (p->next_ != nullptr)
        {
            p = p->next_;
        }
        Node *node = new Node();
        node->data_ = data;
        p->next_ = node;
    }

    void insertHead(int data)
    {
        Node *node = new Node();
        node->data_ = data;
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    void deleteNode(int data)
    {
        Node *pre = head_;
        Node *p = head_->next_;
        while (p != nullptr)
        {
            if (p->data_ == data)
            {
                pre->next_ = p->next_;
                delete p;
                return;
            }
            else
            {
                pre = p;
                p = p->next_;
            }
        }
    }

    void deleteNodeall(int data)
    {
        Node *pre = head_;
        Node *p = head_->next_;
        while (p != nullptr)
        {
            if (p->data_ == data)
            {
                pre->next_ = p->next_;
                delete p;
                // 对指针p重置
                p = pre->next_;
            }
            else
            {
                pre = p;
                p = p->next_;
            }
        }
    }

    bool findNode(int data)
    {
        Node *current = head_->next_; // 从头结点的下一个节点开始遍历 避免直接操作head节点
        while (current != nullptr)
        {
            if (current->data_ == data)
            {
                return true;
            }
            current = current->next_;
        }
        return false;
    }

    void print()
    {
        Node *p = head_->next_;
        while (p != nullptr)
        {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

private:
    friend int GetLaskKNode(Clink& link, int k, int &val);
    friend void reverse(Clink &clink);
    friend void MergeLink(Clink &clink1, Clink &clink2);
    Node *head_;
};

// 单链表逆序
void reverse(Clink &link)
{
    Node *head = link.head_;
    Node *p = head->next_;
    if (p == nullptr)
    {
        return;
    }

    head->next_ = nullptr;

    while (p != nullptr)
    {
        Node *q = p->next_; // 保存p的下一个节点

        // p指针指向的节点进行头插
        p->next_ = head->next_;
        head->next_ = p;

        p = q;
    }
}

int GetLaskKNode(Clink& link, int k, int &val)
{
    Node *p = link.head_->next_;
    Node *q = link.head_->next_;

    while (k--)
    {
        q = q->next_;
    }

    while (q != nullptr)
    {
        p = p->next_;
        q = q->next_;
    }
    val = p->data_;
    return val;
}
int main()
{
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int val = rand() % 100;
        link.insertTail(val);
    }
    link.print();

    reverse(link);
    link.print();

    int kval;
    int k = 2;
    if (GetLaskKNode(link, k, kval))
    {
        cout << "倒数第" << k << "个节点的值:" << kval << endl;
    }
}