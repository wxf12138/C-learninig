#include <iostream>
using namespace std;

class A
{
public:
  virtual void func() { cout << "call A::func()" << endl; }
  void operator delete(void *ptr)
  {
    cout << "call A::operator delete()" << ptr << endl;
  }

private:
  int ma;
};

class B : virtual public A
{
public:
  virtual void func() { cout << "call B::func()" << endl; }
  void *operator new(size_t size)
  {
    void *p = malloc(size);
    cout << "call B::operator new()" << p << endl;
    return p;
  }

private:
  int mb;
};

/*
A a; 4个字节
B b; 8个字节 + 4 = 12字节 vbptr
linux:
*** Dumping AST Record Layout
         0 | class A
         0 |   (A vtable pointer)
         8 |   int ma
           | [sizeof=16, dsize=12, align=8,
           |  nvsize=12, nvalign=8]

*** Dumping AST Record Layout
         0 | class B
         0 |   (B vtable pointer)
         8 |   int mb
        16 |   class A (virtual base)
        16 |     (A vtable pointer)
        24 |     int ma
           | [sizeof=32, dsize=28, align=8,
           |  nvsize=12, nvalign=8]

                         内存分配(虚基类) 虚基类要放到派生类内存的最后面
| 0-7: B的vtable指针 | 8-11: mb | 12-15: 填充（对齐到8字节） |
| 16-23: A的vtable指针 | 24-27: ma | 28-31: 填充（对齐到8字节） |
                         内存分配(普通类)
        | 0-7: A的虚表指针 | 8-11: ma | 12-15: mb |


*/

int main()
{
  // 基类指针指向派生类对象，永远指向的是派生类基类部分数据的起始地址
  // 堆
  A *p = new B();
  cout << "main p :" << p << endl;
  p->func();
  cout << "Address of B object: " << (void *)p << endl;
  cout << "Address of A subobject inside B: " << (A *)p << endl;

  delete p;

  cout << sizeof(A) << endl;
  cout << sizeof(B) << endl;

  // 栈
  // B b;
  // A *p = &b;
  // cout << "main p :" << p << endl;
  // p->func();
  return 0;
}