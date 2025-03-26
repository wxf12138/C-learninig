#include <iostream>
using namespace std;
class A
{
    public:
        A(int data) : ma(data) {cout << "A" << endl;}
        ~A(){cout << "~A()" << endl;}
    protected:
        int ma;
};

class B : virtual public A
{
    public:
        B(int data) : A(data), mb(data) {cout << "B" << endl;}
        ~B(){cout << "~B()" << endl;}
    protected:
        int mb;
};

class C : virtual public A
{
    public:
        C(int data) : A(data), mc(data) {cout << "C" << endl;}
        ~C(){cout << "~C()" << endl;}
    protected:
        int mc;
};

class D : public B, public C
{
    public:
        // 用虚继承A后，D无法通过B、C调用A的构造函数，需要D主动调用A的    
    D(int data) : A(data), B(data), C(data), md(data) {cout << "D" << endl;}
        ~D(){cout << "~D()" << endl;}
    protected:
        int md;
};

int main()
{
   D d(10);
    return 0;
}