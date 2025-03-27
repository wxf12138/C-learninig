#include <iostream>
#include <memory>
#include <thread>
#include <functional>
using namespace std;    

template<typename T>
class MyDeletor
{
    public:
        void operator()(T* p)
        {
            cout << "MyDeletor::operator()" << endl;
            delete[] p;
        }
};
template<typename T>
class MyFileDeletor
{
    public:
        void operator()(T* p)
        {
            cout << "MyFileDeletor::operator()" << endl;
            fclose(p);
        }
};

int main()
{
    // unique_ptr<int, MyDeletor<int>> p1(new int[100]);
    // unique_ptr<FILE, MyFileDeletor<FILE>> p2(fopen("test.txt", "w"));

    // lambda 表达式 ——》  函数对象 function
    unique_ptr<FILE, function<void(FILE*)>> ptr1(fopen("test.txt", "w"),
        [](FILE *p)->void {
            cout << "lambdaw MyFILEDeletor::operator()" << endl;
            fclose(p);
        }
    );
    return 0;
}