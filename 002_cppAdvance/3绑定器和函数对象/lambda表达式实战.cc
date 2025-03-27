#include<algorithm>
#include<iostream>
#include<vector>
#include <functional>
#include <map>
#include <memory>
#include <queue>
using namespace std;

class Data
{
    public:
        Data(int a = 10, int b = 20): _ma(a), _mb(b) {}
    int _ma, _mb;
};
/* 
    lambda 表达式只能用在语句当中， 如果跨语句使用之前定义好的lamba表达式， 那么用什么类型标书lambda表达式
    lambda-》函数对象
*/
int main()
{
    #if 0
    map<int, function<int(int,int)>> caculatorMap;

    caculatorMap[1] = [](int a, int b)->int {return a + b;};
    caculatorMap[2] = [](int a, int b)->int {return a - b;};
    caculatorMap[3] = [](int a, int b)->int {return a * b;};
    caculatorMap[4] = [](int a, int b)->int {return a / b;};

    cout << "number" <<endl;
    int a, b;
    cin >> a >> b;
    cout << "choice";
    int choice;
    cin >> choice;
    cout << caculatorMap[choice](a, b) << endl;
    #endif

    // //智能指针自定义删除器 delete p;
    // unique_ptr<FILE, function<void(FILE*)>> ptr1(fopen("test.txt", "w"), [](FILE *p){fclose(p);});

    //优先级队列
    //priority_queue<Data> queue;
    //priority_queue<Data, vector<Data>, function<bool(Data, Data)>> queue([](Data a, Data b){return a._ma < b._ma;});
    using FUNC = function<bool(Data&, Data&)>;
    priority_queue<Data, vector<Data>, FUNC> maxHeap([] (Data& a, Data& b)->bool {return a._ma < b._ma;});

    maxHeap.push(Data(1, 2));
    maxHeap.push(Data(2, 3));
    maxHeap.push(Data(3, 4));

}