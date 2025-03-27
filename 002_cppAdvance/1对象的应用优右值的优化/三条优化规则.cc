#include <iostream>
using namespace std;
/*
    1. 函数传递过程中，对象优先按引用传递，不要按值传递
    2. 函数返回对象的时候，应该优先返回一个临时对象，而不是返回一个定义过的对象
    3. 函数返回的是对象的值，优先按初始化的方式接收，不要按赋值的方式接收
 */
class Test
{
public:
    Test(int data = 10) : ma(data) { cout << "Test(" << ma << ")" << endl; }
    ~Test() { cout << "~Test(" << ma << ")" << endl; }
    Test(const Test& t) : ma(t.ma) { cout << "Test(const Test& t)" << endl; }
    void operator = (const Test& t) 
    {
        cout << "operator =" << endl;
        ma = t.ma;
    }
    int getData() const { return ma; }
private:
    int ma;
};

Test GetObject(Test &t) // 不能返回局部的或者临时的对象的指针或引用  1. 函数传递过程中，对象优先按引用传递，不要按值传递
{
    cout << "-----------" << endl;
    int val = t.getData();
    cout << "------------" << endl;
    //Test tmp(val);
    return Test(val);//2. 函数返回对象的时候，应该优先返回一个临时对象，而不是返回一个定义过的对象
    
}

int main()
{
    Test t1;
    //Test t2;
    cout << "-------------" << endl;
    Test t2 = GetObject(t1);//    3. 函数返回的是对象的值，优先按初始化的方式接收，不要按赋值的方式接收

    return 0;
}