#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <memory>
using namespace std;
/*
有1亿个整数，最大值不超过1亿，问都有哪些元素重复了？谁是第一个重复的？谁是第一个不重复的(1个位保存数据的状态，2个位保存数据的状态)？
内存限制100M

1亿 = 100M
100M * 4 = 400M * 2 = 800M

位图算法     
int bitmap[100000000/32+1]   3.2M

缺陷:   int 20亿    unsigned int 40亿
1 3 1000000000
int bitmap[1000000000/32+1]  30M

3*4 = 12 * 2 = 24byte

推荐的数据序列：数据的个数 >= 序列里面数字的最大值相当
*/

int main()
{
    vector<int> vec{ 12,78,90,78,123,8,9,90 };
    int max = vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] > max)
            max = vec[i];
    }
    int* bitmap = new int[max / 32 + 1]();// 括号的作用是初始化位图为0
    unique_ptr<int> ptr(bitmap);

    // 找第一个重复出现的数字
    for (auto key : vec)
    {
        int idx = key / 32;
        int offset = key % 32;

        if (0 == (bitmap[idx] & (1 << offset)))
        {
            // key没有重复出现过 
            bitmap[idx] |= (1 << offset); 
        }
        else
        {
            //cout << key << "是第一个重复出现的数字" << endl;
            //return 0;
            cout << key << "重复出现过!" << endl;
        }
    }
}