#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

class SeqStack
{
public:
    SeqStack(int size = 10)
    : mtop(0)
    , mcap(size)
    {
        mpstack = new int[mcap];
    }
    ~SeqStack()
    {
        delete[] mpstack; 
        mpstack = nullptr;
    }

public:
    void push(int val)
    {
        if(mtop==mcap){
            //栈扩容
            expand(2 * mcap);
        }
        mpstack[mtop++] = val;
    }

    void pop()
    {
        if(mtop == 0)
            return;
        mtop--;
    }

    int top() const
    {
        if(mtop == 0)
            throw "stack is empty";
        return mpstack[mtop-1];
    }

    bool empty()
    {
        return mtop == 0;
    }

    int size() const {return mtop;}

private:
    void expand(int size)
    {
        int *p = new int[size];//开辟新内存
       memcpy(p, mpstack, mtop*sizeof(int));//copy
       delete []mpstack;//删除旧空间
       mpstack = p;//指向新内存
       mcap = size;//更新cap
    }
private:
    int* mpstack;
    int mtop;
    int mcap;
};

int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	SeqStack s;
	
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