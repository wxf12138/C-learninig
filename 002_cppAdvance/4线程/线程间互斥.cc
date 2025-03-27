#include <iostream>
#include <thread>
#include <mutex>
#include <list>
/*
    线程间互斥

    多线程程序
    竞态条件：多线程执行的结果是一致的，不会随着cpu对线程不同的调用顺序，而产生不同的结果
    lock_guard
    unique_lock
*/
int ticket_count = 100;
std::mutex mtx;
void sellTicket(int index)
{

    while (ticket_count > 0) // 锁+双重判断
    {

        // mtx.lock();
        {
            std::lock_guard<std::mutex> lock(mtx);
            //std::unique_lock<std::mutex> lock(mtx);
            //lock.lock();
            if (ticket_count > 0)
            {
                std::cout << ticket_count << " " << index << std::endl;
                ticket_count--;
            }
            //lock.unlock();
            // mtx.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
int main()
{
    std::list<std::thread> tlist;
    for (int i = 0; i < 3; i++)
    {
        tlist.push_back(std::thread(sellTicket, i));
    }

    for (auto &t : tlist)
    {
        t.join();
    }

    std::cout << "main thread end" << std::endl;
}