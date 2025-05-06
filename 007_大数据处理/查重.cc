#include <iostream>
#include <vector>
#include <unordered_set> 
#include <unordered_map>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;


#if 0
int main()
{
    string src = "jjhfgiyurtytrs";
    // 找出第一个没有重复出现过的字符
    unordered_map<char, int> m;
    for (auto ch : src)
    {
        auto it = m.find(ch);
        if (it == m.end())
        {
            m.emplace(ch, 1);
        }
        else
        {
            it->second += 1;
        }
    }

    for (auto ch : src)
    {
        if (m[ch] == 1)
        {
            cout << "第一个没有重复过的字符为：" << ch << endl;
            return 0;
        }
    }
    cout << "没有" << endl;
}
#endif


#if 0
int main()
{
    vector<int> vec;
    srand(time(NULL));
    
    for(int i = 0; i < 10000; i++)
    {
        vec.push_back(rand() % 10000);
    }

    // 找第一个重复的数字(+ break) 统计所用重复数字(无 break)
    // unordered_set<int> s1;
    // for (auto key : vec)
    // {
    //     auto it = s1.find(key);
    //     if (it == s1.end())
    //     {
    //         s1.insert(key);
    //     }
    //     else
    //     {
    //         cout << "key: " << key << endl;
    //     }
    // }

    // 统计重复数字以及出现次数
    // unordered_map<int, int> m1;
    // for (int key : vec)
    // {
    //     // pair first second
    //     // auto it = m1.find(key);
    //     // if (it == m1.end())
    //     // {
    //     //     m1.emplace(key, 1);
    //     // }
    //     // else
    //     // {
    //     //     it->second += 1;
    //     // }
    //     m1[key]++;
    // }

    // for (auto pair : m1)
    // {
    //     if (pair.second > 1)
    //     {
    //         cout << "key: " << pair.first << " cnt: " << pair.second << endl;
    //     }
    // }

    // 一组数据是重复的， 去重 使用unordered_multiset
    unordered_multiset<int> s1;
    for (auto key : vec)
    {
        s1.emplace(key);
    }
}
#endif

/*
查重的面试相关问题

有两个文件分别是a和b，里面放了很多ip地址(url地址、email地址)，让你找出来两个文件重复的ip，输出出来

==> 把a文件中所有的ip存放在一个哈希表中，然后依次遍历文件b里面的ip，每
遍历一个ip，在哈希表中搜索一下，搜到的，即是两个文件重复的ip并输出
    用到了哈希表的查询O(1)

有两个文件分别是a和b，各自存放在约1亿条ip地址，每个ip地址是4个字节限制内存使用100M，让找出来两个文件中重复的ip地址并输出

*/
