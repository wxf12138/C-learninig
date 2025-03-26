#include<iostream>
using namespace std;

class Test
{
    public:
    void func() {
        cout<<"call Test::func"<<endl;
    }
    static void static_func(){
        cout<<"call Test::static_func"<<endl;
    }
    int ma;
};

int main()
{
    Test t1;
    Test *t2 = new Test();

    int Test::*p = &Test::ma;

    t1.*p = 20;
    cout << t1.ma << endl;

    t2->*p = 30;
    cout << t2->ma << endl;

    void (Test::*pfunc)() = &Test::func;//成员函数的指针自带一个this指针因此需要引用
    (t1.*pfunc)();
    
    void(*pstatic)() = Test::static_func;
    (*pstatic)();

    return 0;
}