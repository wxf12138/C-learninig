#include <iostream>
#include <vector>
#include <unordered_set> 
#include <unordered_map>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

int main()
{
    vector<int> vec;
    srand(time(NULL));
    
    for(int i = 0; i < 10000; i++)
    {
        vec.push_back(rand() % 10000);
    }

    // 找第一个重复的数字(+ break) 统计所用重复数字(无 break)
    unordered_set<int> s1;
    for (auto key : vec)
    {
        auto it = s1.find(key);
        if (it == s1.end())
        {
            s1.insert(key);
        }
        else
        {
            cout << "key: " << key << endl;
        }
    }
}