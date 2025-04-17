#include <iostream>
using namespace std;

// 定义双向链表节点类型
struct Node
{
    Node(int data = 0)
        : data_(data), next_(nullptr), pre_(nullptr) {}
    int data_;
    Node *next_;
    Node *pre_;
};

// 双向循环链表
class DoubleCircleLink
{
public:
    DoubleCircleLink()
    {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }
    ~DoubleCircleLink()
    {
        Node *p = head_->next_;
        while (p != head_)
        {
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;
            p = head_->next_;
        }
        delete head_;
        head_ = nullptr;
    }

public:
    // 头插法
    void InsertHead(int val)
    {
        Node *node = new Node(val);
        // 要分链表为空和链表不为空两种情况
        if (head_->next_ == nullptr)
        {
            head_->next_ = node;
            node->pre_ = head_;
        }
        else
        {
            node->next_ = head_->next_;
            head_->next_->pre_ = node;
            head_->next_ = node;
            node->pre_ = head_;
        }
    }

    void InsertTail(int val)
    {
        Node *p = head_->pre_; //尾节点
        Node *node = new Node(val);
        //尾插不需要找尾节点
        node->pre_ = p;
        p->next_ = node;
        node->next_ = head_;
        head_->pre_ = node;
    }

    void Show()
    {
        Node *p = head_->next_;
        while (p != head_)
        {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

    void Remove(int val)
    {
        Node *p = head_->next_;
        while (p != head_)
        {
            if (p->data_ == val)
            {
                // 更新后向指针
                p->pre_->next_ = p->next_;
                if (p->next_ != nullptr)
                {
                    // 更新前向指针
                    p->next_->pre_ = p->pre_;
                }
                // Node* next = p->next_;
                delete p;
                // p = next;
                return;
            }
            else
            {
                p = p->next_;
            }
        }
    }

private:
    Node *head_;
    Node *tail_;
};

int main()
{
    DoubleCircleLink dlink;

    dlink.InsertHead(100);

    dlink.InsertTail(20);
    dlink.InsertTail(12);
    dlink.InsertTail(78);
    dlink.InsertTail(32);
    dlink.InsertTail(7);
    dlink.InsertTail(90);
    dlink.Show();

    dlink.InsertHead(200);
    dlink.Show();

    dlink.Remove(200);
    dlink.Show();

    dlink.Remove(90);
    dlink.Show();

    dlink.Remove(78);
    dlink.Show();
}