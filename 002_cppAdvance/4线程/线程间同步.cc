#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

/* 
    1,线程间的互斥
    竞态条件 -》 临界区代码段 -》 保证原子操作 -》 互斥锁mutex 轻量级的无锁机制实现CAS
    strace ./a.out -> pthread_mutex_t
    2,线程间通信
    生产者消费者线程模型
*/
std::mutex mutex;               //定义互斥锁，做线程的互斥操作
std::condition_variable cond;   //定义条件变量，做线程间的同步通信

//生产者生产一个物品，通知消费者消费一个；消费完了在通知生产者继续
class Queue{
    public:
        void put(int val){
            std::unique_lock<std::mutex> lck(mutex);
            while(!q.empty()){
                //q 不为空，生产者应该通知消费者去消费，消费完了，再继续生产
                //生产者线程应该进入阻塞态，并且把mutex互斥锁释放掉
                //1 进入等待状态 2 释放互斥锁
                cond.wait(lck);
            }
            q.push(val);
            cond.notify_all();//通知所有线程，可以进行消费了
            std::cout << "生产者 生产：" << val << "号物品" << std::endl;
        }

        int get(){
            std::unique_lock<std::mutex> lck(mutex);
            while(q.empty()){
                //q 为空，消费者应该通知生产者去生产，生产完了，再继续消费
                //消费者线程应该进入阻塞态，并且把mutex互斥锁释放掉
                //1 进入等待状态 2 释放互斥锁
                cond.wait(lck);
            }
            int val = q.front();
            q.pop(); 
            cond.notify_all(); //通知所有线程，可以进行生产了
            std::cout << "消费者 消费：" << val << "号物品" << std::endl;
            return val;
        }
    private:
        std::queue<int> q;
};

void producer(Queue* que){
    for(int i = 0; i < 10; i++){
        que->put(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void consumer(Queue* que){
    for(int i = 0; i < 10; i++){
        que->get();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
int main()
{
    Queue que; //两个线程共享的队列

    std::thread t1(producer, &que);
    std::thread t2(consumer, &que);

    t1.join();
    t2.join();

    return 0;
}