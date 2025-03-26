#include <iostream>
#include <string.h>
using namespace std;
#if 0 
class Animal{
    public: 
    Animal(string name) : _name(name){}
    virtual void bark()=0;
    protected:
    string _name;
};

class Cat : public Animal{
    public:
    Cat(string name) : Animal(name){}
    void bark(){cout << _name << "bark: mmm " << endl;}
};

class Dog : public Animal{
    public:
    Dog(string name) : Animal(name){}
    void bark(){cout << _name << "bark: www " << endl;}
};

int main()
{
    Animal *p1 = new Cat("kafei");
    Animal *p2 = new Dog("gou");
    
    int* p11 = (int*)p1;
    int* p22 = (int*)p2;
    int temp = p11[0];
    p11[0] = p22[0];
    p22[0] = temp;

    p1->bark();
    p2->bark();
}
#endif
#if 0
class Base{
    public:
    virtual void show(){
        cout << "call Base::show i: "  << endl;
    }
};

class Derive : public Base{
    private:
    void show(){
        cout << "call Derive::show i: "  << endl;
    }
    protected:
    int m_i;
};

int main()
{
    Base *p = new Derive();//基类指针指向派生类对象，并且基类自定义了构造函数，需要基类用虚析构函数析构派生类
    /*
    编译器编译先读取Base中的10  
    push 0AH -> 函数调用参数压栈是在编译时期就确定好的
    mov eax, dword ptr [p]
    mov ecx, dword ptr [eax]
    call ecx
     */
    p->show();//动态绑定 p -> Derive vfptr -> Derive vftable  最终能调用到Derive::show()是运行期间确定的 访问限制符只限制编译阶段
    delete p;

}
#endif

class Base
{
public:
	Base()
	{
		/*
		push ebp
		mov ebp, esp
		sub esp, 4Ch
		rep stos esp<->ebp 0xCCCCCCCCC
		vfptr <- &Base::vftable
		*/
		cout << "call Base()" << endl;
		clear();
	}
	void clear() { memset(this, 0, sizeof(*this)); }
	virtual void show()
	{
		cout << "call Base::show()" << endl;
	}
};

class Derive : public Base
{
public:
	Derive()
	{
		/*
		push ebp
		mov ebp, esp
		sub esp, 4Ch
		rep stos esp<->ebp 0xCCCCCCCCC
		vfptr <- &Derive::vftable
		*/
		cout << "call Derive()" << endl;
	}
	virtual void show()
	{
		cout << "call Derive::show()" << endl;
	}
};

int main()
{
	//Base* pb1 = new Base();
	/*
	mov eax, dword ptr[pb1]
	mov ecx, dword ptr[eax] eax:0x00000000 不是Base::vftable
	call ecx
	*/
	// pb1->show();
	// delete pb1;

	// 正常运行
	Base* pb2 = new Derive();
	pb2->show();
	delete pb2;

	return 0;
}