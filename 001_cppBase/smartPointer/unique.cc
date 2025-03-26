#include <iostream>
#include <memory>

class Test {
public:
    Test() { std::cout << "Test_unique Constructor\n"; }
    ~Test() { std::cout << "Test_unique Destructor\n"; }
    void show() { std::cout << "Test show()\n"; }

    int x = 0;
};

int main() {
    // unique_ptr
    //std::unique_ptr<Test> ptr1 = std::make_unique<Test>();  // 创建对象 c++11
    std::unique_ptr<Test> ptr1(new Test());
    ptr1->show();
    ptr1->x = 1;

    // std::unique_ptr<Test> ptr2 = ptr1; // ❌ 编译错误，不能复制
    std::unique_ptr<Test> ptr2 = std::move(ptr1); // ✅ 通过 move 进行所有权转移 

    if (!ptr1) {
        std::cout << "ptr1 is now nullptr" << ptr2->x <<std::endl;
    }

    return 0;
}
