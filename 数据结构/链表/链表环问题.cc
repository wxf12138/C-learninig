#include <iostream>
using namespace std;

// 节点类型
struct Node
{
    Node(int data = 0) :data_(data), next_(nullptr) {}
    int data_;
    Node* next_;
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
    friend void reverse(Clink &clink);
    friend void MergeLink(Clink &clink1, Clink &clink2);
    Node *head_;
};

bool IsLinkHasCircle(Node *head, int &val)
{
    Node *fast = head;
    Node *slow = head;

    while (fast != nullptr && fast->next_ != nullptr)
    {
        slow = slow->next_;
        fast = fast->next_->next_;

        if (slow == fast)
        {
            // 快慢指针相遇，存在环
            fast = head;
            while (fast != slow)
            {
                slow = slow->next_;
                fast = fast->next_;
            }
            val = fast->data_;

            // 存在环
            return true;
        }
    }
    return false;
}

int main()
{
    Node head;

    Node n1(25), n2(67), n3(32), n4(18);
    head.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;
    n4.next_ = &n4;

    int val;
    if (IsLinkHasCircle(&head, val))
    {
        cout << "链表存在环，环的入口节点是：" << val << endl;
    }
}