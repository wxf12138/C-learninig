#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

template<typename Iterator, typename Compare>
Iterator my_find_if(Iterator first, Iterator last, Compare compare)
{
    for (; first != last; ++first)
    {
        if (compare(*first))
        {
            return first;
        }
    }
    return last;
}

template <typename Compare, typename T>
class _mybind2nd
{
public:
    _mybind2nd(Compare comp, T val) : _comp(comp), _val(val) {}

    bool operator()(const T &first) const
    {
        return _comp(first, _val);
    }

private:
    Compare _comp;
    T _val;
};

template<typename Compare, typename T>
_mybind2nd <Compare, T> mybind2nd(Compare comp, const T &val)
{
    //直接使用函数模板好处是可以直接进行类型的推演
    return _mybind2nd<Compare, T>(comp, val);
}

template <typename Container>
void showContainer(Container &con)
{
    typename Container::iterator it = con.begin();
    for (; it != con.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
};

int main()
{
    vector<int> vec;
    srand(time(nullptr));
    for (int i = 0; i < 20; ++i)
    {
        vec.push_back(rand() % 100 + 1);
    }
    showContainer(vec);

    sort(vec.begin(), vec.end(), greater<int>());
    showContainer(vec);

    auto it1 = my_find_if(vec.begin(), vec.end(), mybind2nd(less<int>(), 70));
    if (it1 != vec.end())
    {
        vec.insert(it1, 70);
    }

    showContainer(vec);
}