#include <iostream>
#include <memory>
using namespace std;
/*
    shared_ptr:强智能指针 可以改变资源引用计数
    weak_ptr:弱智能指针 不可以 operator  lock方法，提升为shared_ptr
    强智能指针循环引用（交叉引用） 是什么问题？ 什么后果？ 怎么解决？
    造成new出来的资源无法释放
    定义对象的时候用强只能指针，引用对象的时候用弱智能指针
*/

class B;
class A
{
public:
    A()
    {
        std::cout << "A()" << std::endl;
    }
    ~A()
    {
        std::cout << "~A()" << std::endl;
    }
    std::weak_ptr<B> pb;
};
class B
{
public:
    B()
    {
        std::cout << "B()" << std::endl;
    }
    ~B()
    {
        std::cout << "~B()" << std::endl;
    }
    std::weak_ptr<A> pa;
};

int main()
{
    shared_ptr<A> spa(new A);
    shared_ptr<B> spb(new B);
    spa->pb = spb;
    spb->pa = spa;
    cout << "spa.use_count() = " << spa.use_count() << endl; // 输出 1
    cout << "spb.use_count() = " << spb.use_count() << endl; // 输出 1

    return 0;
}