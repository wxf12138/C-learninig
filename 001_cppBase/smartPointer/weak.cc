#include <iostream>
#include <memory>

class Test {
public:
    Test() { std::cout << "Test_weak Constructor\n"; }
    ~Test() { std::cout << "Test_weak Destructor\n"; }
    void show() { std::cout << "Test show()\n"; }
};

int main() {
    // std::shared_ptr<Test> sp = std::make_shared<Test>(); //c++14语法
    std::shared_ptr<Test> sp(new Test());
    std::weak_ptr<Test> wp = sp; // 创建弱引用，不影响引用计数

    if (auto ptr = wp.lock()) { // 获取 shared_ptr，检查对象是否仍然存在
        ptr->show();
    } else {
        std::cout << "Object already deleted\n";
    }

    sp.reset(); // 手动释放 shared_ptr

    if (auto ptr = wp.lock()) {
        ptr->show();
    } else {
        std::cout << "Object already deleted\n";
    }

    return 0;
}
