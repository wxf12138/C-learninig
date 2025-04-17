#include <iostream>
using namespace std;

// 定义双向链表节点类型
struct Node
{
    Node(int data = 0)
        : data_(data)
        , next_(nullptr)
        , pre_(nullptr) {}
    int data_;
    Node *next_;
    Node *pre_;
};

// 双向链表
class DoubleLink
{
public:
    DoubleLink()
    {
        head_ = new Node();
    }
    ~DoubleLink()
    {
        Node *p = head_;
        while (p != nullptr)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
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
        Node *node = new Node(val);
        Node *p = head_->next_;
        // 定位到尾节点
        while (p->next_ !=nullptr)
        {
            p = p->next_;
        }

        p->next_ = node;
        node->pre_ = p;
    }

    void Show()
    {
        Node *p = head_->next_;
        while(p != nullptr)
        {
             cout << p->data_ << " ";
             p = p->next_;
        }
        cout << endl;
    }

    void Remove(int val)
    {
        Node *p = head_->next_;
        while(p != nullptr)
        {
            if (p->data_ == val)
            {
                // 更新后向指针
                p->pre_->next_ = p->next_;
                if (p->next_ != nullptr)
                {
                    //更新前向指针
                    p->next_->pre_ = p->pre_;
                }
                //Node* next = p->next_;
                delete p;
                //p = next;
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
};

int main()
{
    DoubleLink dlink;

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