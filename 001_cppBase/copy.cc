#include <iostream>
#include <string>
//深拷贝
class MyClass {
public:
    int* data;
public:
    // 默认构造函数
    MyClass(int value = 0) {
        data = new int(value);
         std::cout << "Constructor Called" << *data << std::endl;
    }

    // 复制构造函数
    MyClass(const MyClass& other) {
         std::cout << "Copy Constructor Called (deep Copy)" << std::endl;
        data = new int(*other.data); // 深拷贝
    }

    // 赋值函数
    MyClass& operator=(const MyClass& other) {
        if (this != &other) { // 防止自赋值
            delete data;      // 释放当前资源 先释放当前对象所占用的外部资源 
            this->data = new int(*other.data); // 深拷贝
            std::cout << "Copy Constructor ==== Called (deep Copy)" << std::endl;
        }
        return *this; // 返回当前对象
    }

      // 打印数据
    void print() const {
        std::cout << "Data: " << *data << ", Address: " << data << std::endl;
    }

    // 析构函数
    ~MyClass() {
        delete data;
        std::cout << "Destructor Called" << std::endl;

    }
};

/* int main() {
    MyClass obj1(10); //构造函数
    std::cout << *obj1.data << "address" << obj1.data << std::endl;
    MyClass obj2 = obj1; // 调用复制构造函数
    std::cout << *obj2.data << "address" << obj2.data << std::endl;
    MyClass obj3;
    obj3 = obj1;         // 调用赋值函数
    std::cout << *obj3.data << "address" << obj3.data << std::endl;
    return 0;
} */



//浅拷贝 导致多个对象共享同一块内存，而当析构函数调用时，这块内存会被释放多次，从而引发了 double free 错误。
/* obj1: Data: 10, Address: 0x55a1bf13beb0
Copy Constructor Called (Shallow Copy)
obj2: Data: 10, Address: 0x55a1bf13beb0
Assignment Operator Called (Shallow Copy)
obj3: Data: 10, Address: 0x55a1bf13beb0
Destructor Called
free(): double free detected in tcache 2
Aborted (core dumped) */

/* class MyClass {
public:
    int* data;
public:
    // 默认构造函数
    MyClass(int value = 0) {
        data = new int(value);
    }

    // 复制构造函数（浅拷贝）
    MyClass(const MyClass& other) : data(other.data) {
        std::cout << "Copy Constructor Called (Shallow Copy)" << std::endl;
    }

    // 赋值函数（浅拷贝）
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            data = other.data; // 直接复制指针
            std::cout << "Assignment Operator Called (Shallow Copy)" << std::endl;
        }
        return *this;
    }

    // 析构函数
    ~MyClass() {
        delete data;
        std::cout << "Destructor Called" << std::endl;
    }

    // 打印数据
    void print() const {
        std::cout << "Data: " << *data << ", Address: " << data << std::endl;
    }

    int getData() const {
        return *data;
    }
    
    
}; */

int main() {
    // 创建对象 obj1
    MyClass obj1(10); //此构造函数输出一个随机的地址（未初始化的data地址）
    std::cout << "obj1: ";
    obj1.print();

    // 使用复制构造函数创建 obj2（浅拷贝）
    MyClass obj2 = obj1;
    std::cout << "obj2: ";
    obj2.print();

    // 使用赋值函数赋值给 obj3（浅拷贝）
    MyClass obj3(10); //此构造函数输出一个随机的地址（未初始化的data地址）
    obj3 = obj1;
    std::cout << "obj3: ";
    obj3.print();  

    

    return 0;
}

