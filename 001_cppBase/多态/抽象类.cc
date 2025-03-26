#include <iostream>
using namespace std;
#include <string>

class Car
{
public:
	Car(string name, double oil) : _name(name), _oil(oil) {}
	double getLeftMiles() {
		return _oil * getMilesPerGallon();//发生了动态绑定
	}
	string getName() { return _name; }
protected:
	string _name;
	double _oil;
    //拥有纯虚函数的类叫做抽象类 抽象类不能实例化对象，但是可以定义指针和引用变量
    virtual double getMilesPerGallon()=0;
};

double showLeftMiles(Car &car)//拥有纯虚函数的类叫做抽象类 抽象类不能实例化对象，但是可以定义指针和引用变量
{
	return car.getLeftMiles();//调用类函数
}

class Benz : public Car
{
public:
	Benz(string name, double oil) : Car(name, oil) {}
	double getMilesPerGallon() { return 19.0; }
};

class BMW : public Car
{
public:
	BMW(string name, double oil) : Car(name, oil) {}
	double getMilesPerGallon() { return 17.0; }
};

class Audi : public Car
{
public:
	Audi(string name, double oil) : Car(name, oil) {}
	double getMilesPerGallon() { return 16.0; }
};

int main()
{
	Benz c1("Benz", 10.0);
	cout << c1.getName() << ": " << showLeftMiles(c1) << endl;
	BMW c2("BMW", 10.0);
	cout << c2.getName() << ": " << showLeftMiles(c2) << endl;
	Audi c3("Audi", 10.0);
	cout << c3.getName() << ": " << showLeftMiles(c3) << endl;


	return 0;
}