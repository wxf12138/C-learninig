#include <iostream>
#include <string>
using namespace std;
#if 0
class Test
{
    public:
        Test(int a = 10) : ma(a) {cout << "Test()" << endl;}
        ~Test() {cout << "~Test()" << endl;}
        Test(const Test &t) : ma(t.ma) {cout << "Test(const Test &t)" << endl;}
        Test& operator=(const Test &t)
        {
            cout << "operator=" << endl;
            ma = t.ma;
            return *this;  
        }

    private:
        int ma;
};

int main()
{
    Test t1;
    Test t2(t1);

    Test t3 = t1;  

    //对于对象构造的优化： 用临时对象生成新对象时，临时对象就不产生了，直接构造新对象就可以了
    Test t4 = Test(20); //显示生成临时对象 生存周期：所在的语句 Test t4(20);

    t4 = t2;
    //先构造再赋值
    t4 = Test(30);
    t4 = (Test)30; // 显式
    t4 = 30; // 隐式

    Test *p = &Test(40); //右值引用中不能取临时对象的地址
    const Test &ref = Test(50);

    return 0;
}
#endif

class Test
{
public:
	Test(int a = 5, int b = 5) : ma(a), mb(b) { cout << "Test(" << ma << ", " << mb << ")" << endl; }
	~Test() { cout << "~Test(" << ma << ", " << mb << ")" << endl; }
	Test(const Test& t) : ma(t.ma), mb(t.mb) { cout << "Test(const Test& t)" << ma << endl; }
	Test& operator = (const Test& t)
	{
		cout << "operator=" << endl;
		ma = t.ma;
		mb = t.mb;
		return *this;
	}
	Test& operator + (const Test& t)
	{
		cout << "operator+" << endl;
		ma = t.ma + ma;
		return *this;
	}
	void setMa(int ma)
	{
		this->ma = ma;
	}
private:
	int ma;
	int mb;
};

Test func(Test t1, Test t2)
{
	Test t = t1 + t2;
	t.setMa(20);
	return t;
}

//Test t1(10, 10);

int main()
{
	Test t1(5, 5);
	Test t2(6);
	cout << "----------------------" << endl;
	t2 = Test(100); // 会显示生成临时对象，会调用构造析构
	cout << "----------------------" << endl;
	t2 = (Test)30; // 会显示生成临时对象，会调用构造析构
	cout << "----------------------" << endl;
	t2 = 40; // 会隐式生成临时对象，会调用构造析构
	cout << "----------------------" << endl;
	//Test* p = &Test(40);  // 不安全的，vs22直接编译不过
	const Test& ref = Test(50); // 是ok的，临时对象不会被马上析构
	cout << "----------------------" << endl;
	Test t7 = func(t1, t2);
	Test t6(20, 20);
	Test t3 = t6;
	Test t5(10, 10);
	const Test& ref = Test(50, 51);
	static Test t4 = Test(24, 24); // 程序运行结束时析构
	cout << "----------------------" << endl;
	Test* p1 = new Test[2];
	delete[] p1;
	return 0;
}


//Test t10(20, 30); // 在main函数执行前构造，main函数结束后析构