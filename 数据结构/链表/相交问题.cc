#include <iostream>
using namespace std;

// 节点类型
struct Node
{
    Node(int data = 0) : data_(data), next_(nullptr) {}
    int data_;
    Node *next_;
};
// 判断两个单链表是否相交，如果相交返回相交节点的值
bool IsLinkHasMerge(Node *head1, Node *head2, int& val)
{
    int cnt1 = 0, cnt2 = 0;
    Node *p = head1->next_;
    Node *q = head2->next_;

    while (p != nullptr)
    {
        cnt1++;
        p = p->next_;
    }

    while (q != nullptr)
    {
        cnt2++;
        q = q->next_;
    }
    p = head1;
    q = head2;
    if (cnt1 > cnt2)
    {
        // 第一个链表长，需要对其前半部分长度
        int offset = cnt1 - cnt2;
        while (offset-- > 0)
        {
            p = p->next_;
        }
    }
    else
    {
        // 第二个链表长
        int offset = cnt2 - cnt1;
        while (offset-- > 0)
        {
            q = q->next_;
        }
    }

    while (p != nullptr && q != nullptr)
    {
        if (p == q)
        {
            val = p->data_;
            return true;
        }
        p = p->next_;
        q = q->next_;
    }
    return false;
}
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
int main()
{
    Node head1;
    Node n1(25), n2(67), n3(32), n4(18);
    head1.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;

    Node head2;
    Node n5(31);
    head2.next_ = &n5;
    n5.next_ = &n1;

    int val;
    if (IsLinkHasMerge(&head1, &head2, val))
    {
        cout << "链表相交，相交节点是：" << val << endl;
    }
}