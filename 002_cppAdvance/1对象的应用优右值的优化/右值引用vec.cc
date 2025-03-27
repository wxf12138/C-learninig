#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;
// 容器空间配置器，和C++标准库的allocator一样
template <typename T>
struct Allocator
{
    T *allocate(size_t size)
    {
        cout << "Alloc_allocate" << endl;
        return (T *)malloc(size * sizeof(T)); // 内存开辟
    }

    void deallocate(T *p)
    {
        cout << "Alloc_deallocate" << endl; // 内存释放
        free(p);
    }
    template<typename Ty>
    void construct(T *p, Ty &&value) // 负责对象构造右值
    {
        cout << "Alloc_construct" << endl; // 定位new
        new (p) T(std::forward<Ty>(value));
    }
    void destroy(T *p)
    {
        cout << "Alloc_destroy" << endl; // 负责对象析构
        p->~T();
    }
};

template <typename T, typename Alloc = Allocator<T>>
class vector
{
public:
    vector(int size = 10)
    {
        //__first = new T[size];
        cout << "vector_construct" << endl;
        __first = __alloc.allocate(size);
        __last = __first;
        __end = __first + size;
    }
    ~vector()
    {
        for (T *p = __first; p != __last; ++p)
        {
            cout << "~vector" << endl;
            __alloc.destroy(p); // 把_first指向的数组有效元素进行析构操作
        }
        __alloc.deallocate(__first); // 释放堆上的数组内存
        __first = __last = __end = nullptr;
    }

    vector(const vector<T> &rhs)
    {
        int size = rhs.__end - rhs.__first;
        //__first = new T[size];
        __first = __alloc.allocate(size); // 内存开辟
        int len = rhs.__last - rhs.__first;
        for (int i = 0; i < len; ++i)
        {
            __alloc.construct(__first + i, rhs.__first[i]); // 在堆上构造对象
        }
        __last = __first + len;
        __end = __first + size;
    }

    vector<T> &operator=(const vector<T> &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        for (T *p = __first; p != __last; ++p)
        {
            __alloc.destroy(p); // 把_first指向的数组有效元素进行析构操作
        }
        __alloc.deallocate(__first); // 释放堆上的数组内存

        int size = rhs.__end - rhs.__first;
        __first = __alloc.allocate(size);
        int len = rhs.__last - rhs.__first;
        for (size_t i = 0; i < len; ++i)
        {
            __alloc.construct(__first + i, rhs.__first[i]); // 在堆上构造对象
        }
        __last = __first + len;
        __end = __first + size;
        return *this;
    }

    template <typename Ty>
    void push_back(Ty &&val)    //函数模板的类型推演 + 引用折叠
    {
        if (full())
            expand();
        //*__last++ = val; forward：类型的完美转发
        __alloc.construct(__last, std::forward<Ty>(val)); // 在_last指针指向的内存构造一个值为val的对象
        __last++;
        cout << "push_back_construct" << endl;
    }
    void pop_back()
    {
        if (empty())
            return;
        verify(__last - 1, __last);
        --__last;
        __alloc.destroy(__last); // 指针--  再析构
    }

    T back() const
    {
        return *(__last - 1);
    }
    bool full() const
    {
        return __last == __end;
    }

    bool empty() const
    {
        return __last == __first;
    }

    int size() const
    {
        return __last - __first;
    }

    T &operator[](int index) const
    {
        if (index < 0 || index >= size())
        {
            throw "OutOfRangeException";
        }
        return __first[index];
    }
    // 迭代器的实现
    class Iterator
    {
    public:
        friend class vector<T, Alloc>;
        Iterator(vector<T, Alloc> *pVec = nullptr, T *p = nullptr)
            : _p(p), _pVec(pVec)
        {
            Iterator_Base *itb = new Iterator_Base(this, _pVec->_head._next);
            _pVec->_head._next = itb;
        }
        bool operator!=(const Iterator &it) const
        {
            if (_pVec == nullptr || _pVec != it._pVec)
            {
                throw "iterator incompatable!";
            }
            return _p != it._p;
        }
        void operator++()
        {
            if (_pVec == nullptr)
            {
                throw "iterator invalid";
            }
            ++_p;
        }
        T &operator*()
        {
            if (_pVec == nullptr)
            {
                throw "iterator invalid";
            }
            return *_p;
        }

    private:
        T *_p;
        // 当前迭代器是哪个容器对象
        vector<T, Alloc> *_pVec;
    };

    Iterator begin()
    {
        return Iterator(this, __first);
    }
    Iterator end()
    {
        return Iterator(this, __last);
    }

    void verify(T *first, T *last)
    {
        Iterator_Base *pre = &this->_head;
        Iterator_Base *it = _head._next;
        while (it != nullptr)
        {
            // 插入/删除操作使迭代器失效
            if (it->_cur->_p >= first && it->_cur->_p <= last)
            {
                // 迭代器失效
                it->_cur->_p = nullptr;
                // 删除当前迭代器节点，继续判断后面的迭代器节点是否失效(链表操作)
                pre->_next = it->_next;
                delete it;
                it = pre->_next;
            }
            else
            {
                pre = it;
                it = it->_next;
            }
        }
    }

    // 自定义容器中insert方法实现
    Iterator insert(Iterator it, const T &val)
    {
        /*
        1.不考虑扩容
        2.不考虑it.ptr的合法性
        */
        verify(it._p - 1, __last);
        T *p = __last;
        while (p > it._p) // 使插入元素后的所有元素后移一位
        {
            __alloc.construct(p, *(p - 1)); // 构造新对象 在p指向的新位置上构造原p-1的值
            cout << "insert_construct p:" << p << " " << *p << endl;
            __alloc.destroy(p - 1); // 析构旧对象
            cout << "insert_destroy p:" << p << " " << *(p - 1) << endl;
            p--;
        }
        __alloc.construct(p, val);
        cout << "the last insert" << endl;
        __last++;
        return Iterator(this, p);
    }

    Iterator erase(Iterator it)
    {
        verify(it._p - 1, __last);
        T *p = it._p;
        while (p < __last - 1)
        {
            __alloc.destroy(p);
            cout << "erase_destroy" << *p << " " << p << endl;
            __alloc.construct(p, *(p + 1));
            cout << "construct" << *(p + 1) << " " << p << endl; // 原来的位置前移
            p++;
        }
        __alloc.destroy(p);
        __last--;
        return Iterator(this, it._p); // 更新迭代器
    }

private:
    T *__first;
    T *__last;
    T *__end;
    Alloc __alloc; // 定义容器的空间配置器对象

    struct Iterator_Base
    {
        // 以面向对象的方式初始化结构体
        Iterator_Base(Iterator *c = nullptr, Iterator_Base *n = nullptr)
            : _cur(c), _next(n)
        {
        }
        Iterator *_cur;
        Iterator_Base *_next;
    };
    Iterator_Base _head;

    void expand()
    {
        int size = __end - __first;
        T *ptmp = __alloc.allocate(size * 2);
        cout << "expand allocate" << endl;
        // 遍历旧内存中从 0 到 size-1 的所有有效对象，
        // 对每个对象调用构造函数，将旧对象拷贝到新内存对应位置
        for (int i = 0; i < size; i++)
        {
            __alloc.construct(&ptmp[i], __first[i]);
            cout << "expand construct " << &ptmp[i] << endl;
            // ptmp[i] = __first[i];
        }
        // 遍历旧内存中所有有效的对象，调用析构函数销毁它们
        for (T *p = this->__first; p != this->__last; ++p)
        {
            __alloc.destroy(p); // 先删除指针
            cout << "expand destroy " << p << endl;
        }
        __alloc.deallocate(__first); // 再释放内存
        __first = ptmp;
        __end = __first + size * 2;
        __last = __first + size;
    }
};

class CMyString
{
public:
    CMyString(const char *p = nullptr)
    {
        if (p != nullptr)
        {
            mptr = new char[strlen(p) + 1];
            strcpy(mptr, p);
        }
        else
        {
            mptr = new char[1];
            *mptr = '\0';
        }
        cout << "CMyString()" << *mptr << endl;
    }
    ~CMyString()
    {
        delete[] mptr;
        mptr = nullptr;
        cout << "~CMyString()" << endl;
    }

    CMyString(const CMyString &str)
    {
        mptr = new char[strlen(str.mptr) + 1];
        strcpy(mptr, str.mptr);
        cout << "CMyString(const CMyString&)" << endl;
    }

    CMyString(CMyString &&str)
    {
        mptr = str.mptr;
        str.mptr = nullptr;
        cout << "CMyString(CMyString&&)" << endl;
    }

    CMyString &operator=(CMyString &str)
    {
        cout << "CMyString& operator=(String&)" << endl;
        if (this == &str)
            return *this;

        delete[] mptr;

        mptr = new char[strlen(str.mptr) + 1];
        strcpy(mptr, str.mptr);

        return *this;
    }

    CMyString &operator=(CMyString &&str)
    {
        cout << "CMyString& operator=(String&&)" << endl;
        if (this == &str)
            return *this;

        delete[] mptr;

        mptr = str.mptr;
        str.mptr = nullptr;

        return *this;
    }
    const char *c_str() const { return mptr; }

private:
    char *mptr;
    friend CMyString operator+(const CMyString &lhs,
                               const CMyString &rhs);
    friend ostream &operator<<(ostream &out, const CMyString &str);
};
int main()
{
    CMyString str1 = "aaaaaaaaaaaaaaaaa";
    vector<CMyString> vec;
    vec.push_back(std::move(str1));
    vec.push_back(CMyString("bbbbbbbbbb"));

    return 0;
}