#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class RefCount
{
public:
    RefCount(T *ptr = nullptr) : mptr(ptr)
    {
        if (mptr != nullptr)
        {
            count = 1;
        }
    }
    int addRef()
    {
        return ++count; //注意原子操作
    }
    int release()
    {
        return --count;
    }

private:
    T *mptr;
    int count;
};
template <typename T>
class CSmartPtr
{
public:
    CSmartPtr(T *ptr = nullptr) : mptr(ptr)
    {
        mpRefCount = new RefCount<T>(mptr);
    }
    CSmartPtr(const CSmartPtr<T> &src)
        : mptr(src.mptr), mpRefCount(src.mpRefCount)
    {
        if (src.mptr != nullptr)
        {
            mpRefCount->addRef();
        }
    }
    ~CSmartPtr()
    {
       if (mpRefCount->release() == 0)
       {
          delete mptr;
          mpRefCount = nullptr;
          delete mpRefCount;
          mptr = nullptr;
       }
    }

    T &operator*() { return *mptr; }
    T *operator->() { return mptr; }
    CSmartPtr<T> &operator=(const CSmartPtr<T> &src)
    {
        if (this == &src)
            return *this;
        if (0 == mpRefCount->release())
        {
            delete mptr;
        }

        mptr = src.mptr;
        mpRefCount = src.mpRefCount;
        mpRefCount->addRef();
        return *this;
    }

private:
    T *mptr;
    RefCount<T> *mpRefCount;
};

int main()
{
    /*
        推荐使用：
        unique_ptr
        unique_ptr(const unique_ptr&)  = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

        unique_ptr<T>& operator=(unique_ptr<T>&&)
     */
    std::unique_ptr<int> p1(new int(10));
    // std::move 得到当前变量的右值类型
    unique_ptr<int> p2(std::move(p1));

    /*
        带引用计数的智能指针shared_ptr 和 weak_ptr
    */
   CSmartPtr<int> p3(new int(10));
   CSmartPtr<int> p4(p3);
    p4 = p3;

    *p3 = 20;
    cout << *p3 << "" << *p4 << endl;
    return 0;
}
