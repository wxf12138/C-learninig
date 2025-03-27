#include <iostream>
#include <thread>
#include <functional>

/* 
    创建启动一个线程：std::thread定义一个线程对象，传入线程所需要的线程函数和参数，线程自动启动
*/
int main()
{
    // 定义函数对象
    std::function<void(int)> func = [](int time) {
        std::cout << "Hello World" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(time));
    };

    // 绑定默认参数 time=1，生成无参的调用对象
    auto bound_func = std::bind(func, 1);
    auto bound_func2 = std::bind(func, 10);

    // 将绑定后的函数对象传递给线程
    std::thread t(bound_func);
    t.join(); //主线程等待子线程结束，主线程继续往下进行

    std::thread t2(bound_func2);
    t2.join();
    //t.detach();//分离线程，线程结束后，线程对象可以继续使用
    std::cout << "Goodbye World" << std::endl;

    //主线程进行完成，等待其他子线程结束, 如果还有未进行完成的子线程，则报错
    //terminate called without an active exception
    //Aborted (core dumped)
    return 0;
}