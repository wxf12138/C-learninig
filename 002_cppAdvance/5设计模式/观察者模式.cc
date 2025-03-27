
/*
    行为型模式：主要关注的是对象之间的通讯
    观察者-监听者模式（发布-订阅模式）， 主要关注的是对象一对多的关系。
    多个对象依赖一个对象，当该对象的状态发生改变时，其他对象都能接收到相应的通知
    Observer1 Observer2
        subject   有改变，应该及时通知observer，去处理相应的事件
*/

#include <iostream>
#include <unordered_map>
#include <list>

// 观察者抽象类
class Observer
{
public:
    // 处理消息的接口
    virtual void handle(int msgid) = 0;
};

class Observer1 : public Observer
{
public:
    void handle(int msgid)
    {
        switch (msgid)
        {
        case 1:
            std::cout << "Observer1 recv 1 msg!" << std::endl;
            break;
        case 2:
            std::cout << "Observer1 recv 2 msg!" << std::endl;
            break;
        default:
            std::cout << "Observer1 recv unknown msg!" << std::endl;
            break;
        }
    }
};

class Observer2 : public Observer
{
public:
    void handle(int msgid)
    {
        switch (msgid)
        {
        case 2:
            std::cout << "Observer2 recv 2 msg!" << std::endl;
            break;
        default:
            std::cout << "Observer2 recv unknown msg!" << std::endl;
            break;
        }
    }
};

class Observer3 : public Observer
{
public:
    void handle(int msgid)
    {
        switch (msgid)
        {
        case 1:
            std::cout << "Observer3 recv 1 msg!" << std::endl;
            break;
        case 3:
            std::cout << "Observer3 recv 3 msg!" << std::endl;
            break;
        default:
            std::cout << "Observer3 recv unknown msg!" << std::endl;
            break;
        }
    }
};

class Subject
{
public:
    //为主题增加观察者对象
    void addObserver(Observer* obser, int msgid)
    {
        //list [id] 重载函数: id如果存在，则返回值，若不存在自动添加
        _subMap[msgid].push_back(obser);
        //auto it = _subMap.find(msgid);
        // if(it != _subMap.end())
        // {
        //     it->second.push_back(obser);
        // }
        // else
        // {
        //     std::list<Observer*> lis;
        //     lis.push_back(obser);
        //     _subMap.insert({msgid, lis});
        // }
    }
    //主题检测发生变化，通知相应的观察者对象处理事件
    void dispatch(int msgid)
    {
        auto it = _subMap.find(msgid);
        if (it != _subMap.end())
        {
            for (Observer *obser : it->second)
            {
                obser->handle(msgid);
            }
        }
        else
        {
            std::cout << "没有观察者订阅该主题" << std::endl;
        }
    }
private:
    std::unordered_map<int, std::list<Observer*>> _subMap; 
};

int main()
{
    Subject sub;
    Observer *p1 = new Observer1();
    Observer *p2 = new Observer2();
    Observer *p3 = new Observer3();

    sub.addObserver(p1, 1);
    sub.addObserver(p1, 2);
    sub.addObserver(p2, 2);
    sub.addObserver(p3, 1);
    sub.addObserver(p3, 3);

    // int msgid = 0;
    // for(;;)
    // {
    //     std::cout << "请输入消息id: ";
    //     std::cin >> msgid;
    //     if(msgid == -1)
    //         break;
    //     sub.dispatch(msgid);
    // }
    sub.dispatch(1);
	sub.dispatch(5);
}