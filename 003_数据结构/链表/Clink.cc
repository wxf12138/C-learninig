#include <iostream>
using namespace std;

// 节点类型
struct Node
{
    Node() : data_(0), next_(nullptr) {}
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

void MergeLink(Clink &clink1, Clink &clink2)
{
    Node *head1 = clink1.head_->next_;
    Node *head2 = clink2.head_->next_;
    Node *last = clink1.head_; // 合并后的链表的尾节点

    while (head1 != nullptr && head2 != nullptr)
    {
        if (head1->data_ < head2->data_)
        {
            // 将 head1 的当前节点连接到合并链表
            last->next_ = head1;
            head1 = head1->next_;
        }
        else
        {
            // 将 head2 的当前节点连接到合并链表
            last->next_ = head2;
            head2 = head2->next_;
        }
        last = last->next_;
        last->next_ = nullptr; // 断开旧连接
    }

    // 处理剩余节点
    if (head1 != nullptr)
    {
        last->next_ = head1;
    }
    else
    {
        last->next_ = head2;
    }

    // 清空 clink2 的头结点（避免重复释放）
    clink2.head_->next_ = nullptr;
}

int main()
{
    /*
    free(): double free detected in tcache 2
    Aborted (core dumped)
    */
// 合并链表
    int arr1[] = {1, 3, 5, 7, 9};
    int arr2[] = {2, 4, 6, 8, 10};
    Clink clink1, clink2;
    for (int i = 0; i < sizeof(arr1) / sizeof(int); i++)
    {
        clink1.insertTail(arr1[i]);
    }
    for (int i = 0; i < sizeof(arr2) / sizeof(int); i++)
    {
        clink2.insertTail(arr2[i]);
    }

    MergeLink(clink1, clink2);
    clink1.print();
}