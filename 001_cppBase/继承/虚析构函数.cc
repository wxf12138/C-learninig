#include <iostream>
using namespace std;


class Base
{
public:
    Base(int data) : ma(data) { cout << "Base()" << endl; }
    //虚析构函数
     virtual ~Base() { cout << "~Base()" << endl; }
    virtual void show() { cout << "call Base::show()" << endl; }
protected:
    int ma;
};
class Derive :public Base
{
public:
    Derive(int data)
        :Base(data), mb(data), ptr(new int(data)) {
        cout << "Derive()" << endl;
    }
    ~Derive() { cout << "~Derive()" << endl; }
    void show() { cout << "call Derive::show()" << endl; }

private:
    int mb;
    int* ptr;
};

int main()
{
    // Derive d(20);
    // Base *p = &d;
    Base* p = new Derive(10);
    p->show();  
    delete p;   //派生类析构函数没有调用

    return 0;
}
