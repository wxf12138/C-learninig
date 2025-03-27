#include <iostream>
class A {
public:
    A() {
        std::cout << "A()" << std::endl;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B {
    A& a;
    public:
    B(A& a) : a(a) {
        std::cout << "B()" << std::endl;
    }
    ~B() {
        std::cout << "~B()" << std::endl;
    }
};

int main() {
    A a;
    B b(a);
    return 0;
}