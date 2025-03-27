#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
using namespace std;
/*
    著名开源网络库muduo库
    多线程访问共享对象的线程安全问题
    有线程库时，编译时要链接 -lpthread
    g++ muduo_test.cc -o muduo_test -lpthread
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

    void function()
    {
        cout << "A::function()" << endl;
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

void handler01(weak_ptr<A> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // 在调用A对象的时候，要判断A对象是否存活
    shared_ptr<A> sp = p.lock();
    if (sp != nullptr)
    {
        sp->function();
    }else
    {
        cout << "A is dead" << endl;
    }
}
int main()
{
    
    {
        shared_ptr<A> p(new A());
        thread t1(handler01, weak_ptr<A>(p));
        
        t1.detach();
    }
    // t1.join();
    std::this_thread::sleep_for(std::chrono::seconds(20));
    return 0;
}