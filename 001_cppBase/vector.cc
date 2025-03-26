#include <iostream>
using namespace std;
// 容器空间配置器，和C++标准库的allocator一样
template <typename T>
struct Allocator
{
    T *allocate(size_t size)
    {
        cout << "allocate" << endl;
        return (T *)malloc(size * sizeof(T)); // 内存开辟
    }

    void deallocate(T *p)
    {
        cout << "deallocate" << endl; // 内存释放
        free(p);
    }

    void construct(T *p, const T &value) // 负责对象构造
    {
        cout << "construct" << endl; // 定位new
        new (p) T(value);
    }

    void destroy(T *p)
    {
        cout << "destroy" << endl; // 负责对象析构
        p->~T();
    }
};

template <typename T, typename Alloc = Allocator<T>>
class vector
{
public:
    vector(int size = 3)
    {
        //__first = new T[size];
        __first = __alloc.allocate(size);
        __last = __first;
        __end = __first + size;
        cout << "vector" << endl;
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

    void push_back(const T &val)
    {
        if (full())
            expand();
        //*__last++ = val;
        __alloc.construct(__last++, val); // 在_last指针指向的内存构造一个值为val的对象
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
        while (p > it._p)//使插入元素后的所有元素后移一位
        {
            __alloc.construct(p, *(p - 1)); // 构造新对象 在p指向的新位置上构造原p-1的值
            cout << "insert_construct p:" << p << " "<< *p << endl;
            __alloc.destroy(p - 1); // 析构旧对象
            cout << "insert_destroy p:" << p  << " "<< *(p-1) << endl;
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
            cout << "construct" << *(p+1) << " " << p << endl;//原来的位置前移
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

class Test
{
public:
    Test()
    {
        cout << "constructTest()" << endl;
    }
    ~Test()
    {
        cout << "destructTest()" << endl;
    }

    Test(const Test &t)
    {
        cout << "copyTest()" << endl;
    }
};

int main()
{
    /*   vector<int> v;
      for (int i = 0; i < 10; i++)
      {
          v.push_back(i);

      }

      v.pop_back();

      while (!v.empty())
      {
          cout << v.back() << " ";
          v.pop_back();
      } */
    // 空间配置器
    /*  vector<Test> v;
   cout << "---------------------------" << endl;
   Test t1, t2, t3;
   cout << "---------------------------" << endl;

   v.push_back(t1);
   v.push_back(t2);
   v.push_back(t3);

   cout << "---------------------------" << endl;
   v.pop_back();
   cout << "---------------------------" << endl;
   return 0; */

    // 迭代器
    /*  vector<int> v;
   for (int i = 0; i < 10; i++)
   {
       v.push_back(i);
   }
   auto it = v.begin();
   for (; it != v.end(); ++it)
   {
       cout << *it << " ";
   }
   cout << endl;

   int size = v.size();
   for (int i = 0; i < size; ++i)
   {
       cout << v[i] << " ";
   }
   cout << endl;

   for (int val : v)
   {
       cout << val << " ";
   }
   cout << endl; */

    // 迭代器失效问题
    vector<int> vec(200); // 当insert扩容后，原来的it会失效，但代码仍然试图运行
    for (int i = 0; i < 6; ++i)
    {
        vec.push_back(rand() % 100 + 1);
    }

    /* auto it1 = vec.end();
    vec.pop_back();
    auto it2 = vec.end();
    cout << (it1 != it2) << endl; */

    // erase
      for (int val : vec)
     {
         cout << val << " ";
     }
     cout << endl;
     auto it = vec.begin();
     while (it != vec.end())
     {
         if (*it % 2 == 0)
         {
             cout << *it << endl;
             it = vec.erase(it);
         }
         else
         {
             ++it;
         }
     }

     for (auto val : vec)
     {
         cout << val << " ";
     }
 
    /* for (int v : vec)
        cout << v << " ";
    cout << endl;

    auto it = vec.begin();
    for (; it != vec.end(); ++it)
    {
        if (*it % 2 == 0)
        {
            it = vec.insert(it, *it - 1);
            for (int v : vec)
            cout << v << " ";
            cout << endl;
            ++it;
        }
    }

    for (int v : vec)
        cout << v << " ";
    cout << endl; */

    return 0;
}