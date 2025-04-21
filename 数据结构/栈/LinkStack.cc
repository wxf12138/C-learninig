#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stack>
using namespace std;

// 中缀转后缀步骤
/* 
    1. 遇到数字直接出栈
    2. 遇到符号，出栈两个数字
    3. 运算两个数字，把结果压栈
*/
bool Priority(char ch, char topch)
{
	if ((ch == '*' || ch == '/') && (topch == '+' || topch == '-'))
		return true;
	if (topch == '(' && ch != ')')
		return true;
	return false;
}

string MiddleToEndExpr(string expr)
{
    string result;
	stack<char> s;

	for (char ch : expr)
	{
		if (ch >= '0' && ch <= '9')
		{
			result.push_back(ch);
		}
		else
		{
			for (;;) 
			{
				// 处理符号了 
				if (s.empty() || ch == '(')
				{
					s.push(ch);
					break;
				}

				// 比较当前符号ch和栈顶符号top的优先级
				char topch = s.top();
				// Priority:true ch > topch   false ch <= topch
				if (Priority(ch, topch))
				{
					s.push(ch);
					break;
				}
				else  
				{
					s.pop();
					if (topch == '(') // 如果遇见)，一直出栈，直到( 括号内优先计算
						break;
					result.push_back(topch);
				}
			}
		}
	}

	// 如果符号栈还存留符号，直接输出到后缀表达式里面     + /
	while (!s.empty())
	{
		result.push_back(s.top());
		s.pop();
	}

	return result;
}
int main()
{
    cout << MiddleToEndExpr("(1+2)*(3+4)") << endl;
}

// 链式栈
#if 0
class LinkStack
{
public:
    LinkStack()
    : size(0)
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
        size++;
    }

    void pop()
    {
        if(head_->next_ == nullptr)
            throw "stack is empty";
        Node* p = head_->next_;
        head_->next_ = p->next_;
        delete p;
        size--;
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
    int size;
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
#endif