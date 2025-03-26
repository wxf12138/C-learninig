#include <iostream>
#include <typeinfo>
using namespace std;



class Base{
    public:
    Base(int data = 10) : ma(data){}
    virtual void show(){cout << "Base::show" << endl;}    
    virtual void show(int){
        cout << "Base::show(int data)" << endl;
    }
    protected:
    int ma;
};

class Derived : public Base{
    public:
    Derived(int data = 20) : Base(data), mb(data){}
    void show(){cout << "Derived::show" << endl;}    
    protected:
    int mb;
};

int main(){
    Derived d(20);
    /*
	pb -> Base Base::show 如果发现show是普通函数，就进行静态绑定

	pb -> Base Base::show 如果发现show是虚函数，就进行动态绑定
	mov eax, dword ptr[pb]  // 取pb指向的派生类对象d的前四个字节vfptr放入eax
	mov ecx, dword ptr[eax] // 将vfptr指向的虚函数地址放入ecx
	call ecx // 动态（运行时期）的绑定（函数的调用）
	*/
    Base *p = &d;
    p->show();  //静态绑定到基类
    p->show(20);    //静态绑定
    cout << sizeof(Base) << endl;    //4
    cout << sizeof(Derived) << endl;    //8
    cout << typeid(p).name() << endl;
    cout << typeid(*p).name() << endl;

    // 用对象本身调用虚函数是静态绑定
    Base b;
    Derived c;
    b.show();//Base::show
    c.show();//Derived::show

    Base *p1 = &b;
    p1->show();
    Base  *p2 = &c;
    p2->show();
    return 0;

}