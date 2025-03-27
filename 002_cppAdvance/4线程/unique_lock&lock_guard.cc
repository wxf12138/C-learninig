#include <thread>
#include <mutex>
#include <condition_variable>

/* 
unique_lock condition_variable
1. unique_lock和lock_guard
2. condition_variable wait和notify_all方法
*/

std::mutex mtx;
std::condition_variable cv;

int main()
{
    //不可能用在函数参数传递或者返回过程中，智能用在简单的临界区代码段的互斥操作中。
    std::lock_guard<std::mutex> lck1(mtx);
    //不仅可以用在简单的临界区代码段的互斥操作中，还能用在函数调用中
    std::unique_lock<std::mutex> lck2(mtx);//不仅自动也可以手动
    cv.wait(lck2);
    //唤醒其他线程，其他线程收到通知，从 等待-》阻塞-》获取互斥锁-》线程继续进行
    cv.notify_all();
} 