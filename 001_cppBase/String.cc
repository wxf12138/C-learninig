#include <iostream>
#include <string.h>
using namespace std;

class String
{
private:
    char *_str;
    int _len;

    friend void display(String &str);
    friend String operator+(ostream &os, String &str);

public:
    String(const char *p = nullptr)
    {
        if (p == nullptr)
        {
            _str = new char[1];
            *_str = '\0';
        }
        else
        {
            _len = strlen(p);
            _str = new char[_len + 1];
            strcpy(_str, p);
        }
    }
    ~String()
    {
        delete[] _str;
        _str = nullptr;
    }
    String(const String &str)
    {
        _str = new char[str._len + 1];
        strcpy(_str, str._str);
    }

    String &operator=(const String &str) // 返回值是类引用，方便链式编程 = =
    {
        if (this == &str)
        {
            return *this;
        }
        else
        {
            delete[] _str;
            _str = new char[str._len + 1];
            strcpy(_str, str._str);
            return *this;
        }
    }

    String operator+(const String &str)
    {
        String temp;
        temp._len = _len + str._len;
        temp._str = new char[temp._len + 1];
        strcpy(temp._str, _str);
        strcat(temp._str, str._str);
        return temp;
    }

    void display()
    {
        cout << _str << endl;
    }
    class Iterator
    {
    public:
        Iterator(char *p = nullptr) : _p(p)
        {
        }
        bool operator!=(const Iterator &it)
        {
            return _p != it._p;
        }
        void operator++()
        {
            ++_p;
        }
        char &operator*()
        {
            return *_p;
        }

    private:
        char *_p;
    };
    Iterator begin()
    {
        return Iterator(_str);
    }

    Iterator end()
    {
        return Iterator(_str + strlen(_str));
    }
};

int main()
{
    String str1("hello");
    auto it = str1.begin();
    for (; it != str1.end(); ++it)
    {
        cout << *it << " " << endl;
    }

    // c++11
    for (char ch : str1)
    {
        cout << ch << " ";
    }
}