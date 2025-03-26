#include <iostream>
using namespace std;
//复制构造函数和赋值函数
class MyClass {
private:
    int* data;
public:
    // 默认构造函数
    MyClass(int value = 0) {
        data = new int(value);
        cout << "Constructor copy called." << data << endl;
    }

    // 复制构造函数
    MyClass(const MyClass& other) {
        data = new int(*other.data); // 深拷贝
        cout << "Copy constructor called." << data << endl;
    }

    // 赋值函数
    MyClass& operator=(const MyClass& other) {
        if (this != &other) { // 防止自赋值
            delete data;      // 释放当前资源
            data = new int(*other.data); // 深拷贝
            cout << "Assignment operator called." << data << endl;
        }
        return *this; // 返回当前对象
    }

    // 析构函数
    ~MyClass() {
        delete data;
    }
};

int main() {
    MyClass obj1(10);
    MyClass obj2 = obj1; // 调用复制构造函数
    MyClass obj3;
    obj3 = obj1;         // 调用赋值函数
    return 0;
}


