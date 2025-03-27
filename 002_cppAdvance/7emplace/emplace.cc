#include <iostream>
// #include <vector>
using namespace std;

class Test
{
public:
    Test(int a) { cout << "Test(int)" << endl; }
    ~Test() { cout << "~Test()" << endl; }
    Test(int a, int b) { cout << "Test(int, int)" << endl; }
    Test(const Test &) { cout << "Test(const Test&)" << endl; }
    Test(Test &&) { cout << "Test(Test &&)" << endl; }
};

// 实现 容器空间配置器
template <typename T>
struct MyAllocator
{
    T *allocate(size_t size)
    {
        return (T *)malloc(size * sizeof(T));
    }
    template <typename... Types>
    void construct(T *ptr, Types &&...args)
    {
        // args只是一个参数，而且是个Test对象，T也是Test类型
        new (ptr) T(forward<Types>(args)...);
    }
};

template <typename T, typename Alloc = MyAllocator<T>>
class vector
{
public:
    vector()
        : vec_(nullptr), size_(0), idx_(0)
    {
    }

public:
    void reserve(size_t size)
    {
        vec_ = allocator_.allocate(size);
        size_ = size;
    }
    /*void push_back(const T& val)
    {
        allocator_.construct(vec_ + idx_, val);//通过allocatedor_构造对象
        idx_++;
    }
    void push_back(T&& val)
    {
        allocator_.construct(vec_ + idx_, move(val));
        idx_++;
    }*/
    template <typename Ty>
    void push_back(Ty &&val)
    {
        allocator_.construct(vec_ + idx_, forward<Ty>(val));
        idx_++;
    }
    template <typename... Types>
    // 引用折叠
    void emplace_back(Types &&...args) // 左值/右值
    {
        // 不管左值还是右值，本质还是左值，需要保持args的引用类型：forward()
        allocator_.construct(vec_ + idx_, forward<Types>(args)...);
        idx_++;
    }
    // 析构函数
    ~vector()
    {
        // 调用已构造元素的析构函数
        for (int i = 0; i < idx_; ++i)
        {
            vec_[i].~T();
        }
        // 释放分配的内存
        free(vec_);
    }

private:
    T *vec_;
    int size_;
    int idx_;
    Alloc allocator_;
};

int main()
{
    Test t1(10);
    vector<Test> vec;
    vec.reserve(100);

    cout << "-----------------" << endl;

    vec.push_back(t1);
    vec.emplace_back(t1);

    cout << "----------------" << endl;

    vec.push_back(Test(20));
    vec.emplace_back(Test(20));

    cout << "----------------" << endl;

    // 直接在容器底层构造对象
    vec.push_back(20);
    vec.emplace_back(39, 10);

    cout << "----------------" << endl;

    /*
    map<int, string> m;
    m.insert(make_pari(1, "hello"));
    m.emplace(2, "world");
    */
}