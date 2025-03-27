#include <iostream>
#include <mutex>

/* 
    单例模式：一个类不管创建多少次对象，永远只得到该类型一个对象的实例
    比如日志模块
    饿汉：还没有获取实例对象，实例对象就已经产生了
    懒汉：唯一的实例对象，知道第一次获取实例对象的时候才创建
*/

// 懒汉单例 线程不安全

std::mutex mtx; 
class Singleton
{
public:
    static Singleton* getInstance() // #3 获取类的唯一实例对象的接口方法
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr)
        {
            /* 
                开辟内存，构造对象，给instance值
            */
            instance = new Singleton();
        }
        return instance;
    }
private:
    static Singleton* instance; // #2 定义一个唯一的类的实例对象
    Singleton() // #1 构造函数私有化
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete; //拷贝构造
    Singleton& operator=(const Singleton&) = delete;//赋值重载
};

Singleton* Singleton::instance = nullptr;

int main()
{
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    Singleton* p3 = Singleton::getInstance();
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;

    return 0;
}