#include <iostream>
#include <memory>
using namespace std;

/* 
    装饰器模式 Decorator
    增加现有类的功能，但是增加现有类功能还可以新增一个子类（导致问题，代码太冗余）
*/

class Car // 抽象基类
{
public:
	virtual void show() = 0;
};

class Bmw : public Car
{
public:
	void show() { std::cout << "this is a bmw car:"; }
};

class Audi : public Car
{
public:
	void show() { std::cout << "this is a audi car:"; }
};

class Benz : public Car
{
public:
	void show() { std::cout << "this is a benz car:"; }
};


class ConcreateDecrator01 : public Car
{
public:
	ConcreateDecrator01(Car* p) : pCar(p) {}
	void show()
	{
		pCar->show();//基类函数
		std::cout << "带定速巡航" << std::endl;
	}
private:
	Car* pCar;
};

class ConcreateDecrator02 : public Car
{
public:
	ConcreateDecrator02(Car* p) : pCar(p) {}
	void show()
	{
		pCar->show();
		std::cout << "带车道保持" << std::endl;
	}
private:
	Car* pCar;
};

class ConcreateDecrator03 : public Car
{
public:
	ConcreateDecrator03(Car* p) : pCar(p) {}
	void show()
	{
		pCar->show();
		std::cout << "带主动刹车" << std::endl;
	}
private:
	Car* pCar;
};

int main()
{
	Car* p1 = new ConcreateDecrator01(new Bmw());
	p1 = new ConcreateDecrator02(p1);
	Car* p2 = new ConcreateDecrator02(new Audi());
	Car* p3 = new ConcreateDecrator03(new Benz());

	p1->show();
	p2->show();
	p3->show();

	return 0;
}