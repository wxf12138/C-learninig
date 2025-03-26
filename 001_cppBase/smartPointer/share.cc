#include <iostream>
#include <memory>

class Test {
public:
    Test() { std::cout << "Test_share Constructor\n"; }
    ~Test() { std::cout << "Test_share Destructor\n"; }
    void show() { std::cout << "Test show()\n"; }
};

int main() {
    //std::shared_ptr<Test> ptr1 = std::make_shared<Test>(); // 创建对象 c++11

    std::shared_ptr<Test> ptr1(new Test());
    std::cout << "Use count: " << ptr1.use_count() << "\n"; // 引用计数

    std::shared_ptr<Test> ptr2 = ptr1; // 共享同一对象

    std::cout << "Use count: " << ptr1.use_count() << "\n"; // 引用计数

    ptr2->show();
    
    return 0;
}
