#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class String
{
public:
	String(const char* p = nullptr)
	{
		if (p != nullptr)
		{
			_pstr = new char[strlen(p) + 1];
			strcpy(_pstr, p);
		}
		else
		{
			_pstr = new char[1];
			*_pstr = '\0';
		}
		cout << "String()" << *(_pstr + 1) << endl;
	}
	~String()
	{
		delete[] _pstr;
		_pstr = nullptr;
		cout << "~String()" << endl;
	}
	String(const String& str)
	{
		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
		cout << "String(const String&)" << endl;
	}
    
	String& operator=(const String& str)
	{
		if (this == &str)
			return *this;
		delete[] _pstr;
		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
		cout << "String& operator=(const String&)" << endl;
		return *this;
	}
	bool operator>(const String& str) const
	{
		return strcmp(_pstr, str._pstr) > 0;
	}
	bool operator<(const String& str) const
	{
		return strcmp(_pstr, str._pstr) < 0;
	}
	bool operator==(const String& str) const
	{
		return strcmp(_pstr, str._pstr) == 0;
	}
	int length() const { return strlen(_pstr); }
	char& operator[](int index) { return _pstr[index]; };
	const char& operator[](int index) const { return _pstr[index]; }
	const char* c_str() const { return _pstr; }
private:
	char* _pstr;
	friend ostream& operator<<(ostream& out, const String& str);
	friend String operator+(const String& lhs, const String& rhs);
};

String operator+(const String& lhs, const String& rhs)
{
	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	String tmp;
	tmp._pstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	strcpy(tmp._pstr, lhs._pstr);
	strcat(tmp._pstr, rhs._pstr); 
	// delete[] ptmp;
	return tmp;
	//return String(ptmp); 会造成内存泄漏，没有释放ptmp占用的空间
}
ostream& operator<<(ostream& out, const String& str)
{
	out << str._pstr;
	return out;
}

String GetString (String& str)
{
    const char* p = str.c_str();
    /* 为什么没有构造函数？
        拷贝构造函数未被调用：
        由于 RVO 优化和赋值操作的存在。
     */
    return String(p);//拷贝构造函数调用 先创建空间 再赋值
}
int main()
{
    String str1("hello");   //普通构造
    String str2;    //普通构造
    str2 = GetString(str1);
    cout << str2.c_str() << endl;
}