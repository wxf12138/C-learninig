#include <iostream>
using namespace std;

class Base{
    public:
    Base(int data = 10) : ma(data){}
    void show(){cout << "Base::show" << endl;}    
    void show(int data = 19){}
    protected:
    int ma;
};

class Derived : public Base{
    public:
    Derived(int data = 20) : Base(data), mb(data){}
    void show(){cout << "Derived::show" << endl;}    
    protected:
    int mb;
};

int main(){
    Base b(10);
    Derived d(20);

    // 基类 《- 派生类
    b = d;

    // 基类 -》 派生类
    //d = b;

    // 基类指针（引用） 《= 派生类
    Base &b1 = d;
    Base *b2 = &d;

    // 派生类指针（引用） =》 基类
    Derived *d1 =(Derived*)&b;//内存非法访问
    return 0;
}