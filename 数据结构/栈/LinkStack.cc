#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
// 链式栈
class LinkStack
{
public:
    LinkStack()
    {
        head_ = new Node;
    }
    ~LinkStack()
    {
        Node* p = head_;
        while (p !=nullptr)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
        
    }
public:
    void push(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    void pop()
    {
        if(head_->next_ == nullptr)
            throw "stack is empty";
        Node* p = head_->next_;
        head_->next_ = p->next_;
        delete p;
    }

    int top() const
    {
        if(head_->next_ == nullptr)
            throw "stack is empty!";
        return head_->next_->data_;
    }

    bool empty() const
    {
        return head_->next_ == nullptr;
    }
private:
    struct Node
    {
        Node(int data = 0)
        : data_(data)
        , next_(nullptr)
        {}
        int data_;
        Node* next_;
    };
    Node* head_;
};

int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	LinkStack s;
	
	for (int v : arr)
	{
		s.push(v);
	}

	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}