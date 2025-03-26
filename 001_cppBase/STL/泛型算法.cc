#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> //包含了c++ stl里面的泛型算法
using namespace std;

/*
    泛型算法 = template + 迭代器 +函数对象
    特点一： 泛型算法的参数接收的都是迭代器
    sort, find, find_if, binary_search, for_each
    特点二： 泛型算法的参数还可以接收函数对象（c函数指针）

    绑定器 + 二元函数对象 -》 一元函数对象
    bind1st: 吧二元函数对象的operator()的第一个参数绑定为指定值
    bind2nd: 吧二元函数对象的operator()的第二个参数绑定为指定值
 */

 int main()
 {
    int arr[] = {14,2,376,4,5,64,7,86,6,16};
    vector<int> v(arr, arr+sizeof(arr)/sizeof(arr[0]));
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl; 

    sort(v.begin(), v.end());
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;

    if (binary_search(v.begin(), v.end(), 376))
    {
        cout << "存在" << endl;
    }
    else
    {
        cout << "不存在" << endl;
    } 

    sort(v.begin(), v.end(), greater<int>());
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;

    //greater a > b ;  less a < b
    auto it2 = find_if(v.begin(), v.end(), bind2nd(greater<int>(), 5));
    v.insert(it2, 555);
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;
    
   
}
