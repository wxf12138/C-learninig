#include <iostream>
#include <vector>
#include "stringhash.h"
#include <string>
using namespace std;

class BloomFilter
{
private:
    int bitSize_;
    vector<int> bitMap_;

public:
    BloomFilter(int bitsize = 1471)
        : bitSize_(bitsize)
    {
        bitMap_.resize(bitSize_ / 32 + 1);
    }
public:
    // 添加元素
    void setBit(const char* str)
    {
        // 计算k组哈希函数的值
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = RSHash(str) % bitSize_;
        int idx3 = APHash(str) % bitSize_;
        
        int idx = 0;
        int offset = 0;
 
        // 把idx1， idx2， idx3这几个位全部置1
        idx = idx1 / 32;
        offset = idx1 % 32;
        bitMap_[idx] |= (1 << offset);

        idx = idx2 / 32;
        offset = idx2 % 32;
        bitMap_[idx] |= (1 << offset);

        idx = idx3 / 32;
        offset = idx3 % 32;
        bitMap_[idx] |= (1 << offset);
    }

    // 查询元素
    bool getBit(const char* str)
    {
         // 计算k组哈希函数的值
         int idx1 = BKDRHash(str) % bitSize_;
         int idx2 = RSHash(str) % bitSize_;
         int idx3 = APHash(str) % bitSize_;
         
        int index = 0;
        int offset = 0;

        index = idx1 / 32;
        offset = idx1 % 32;
        if (0 == (bitMap_[index] & (1 << offset)))
        {
            return false;
        }

        index = idx2 / 32;
        offset = idx2 % 32;
        if (0 == (bitMap_[index] & (1 << offset)))
        {
            return false;
        }

        index = idx3 / 32;
        offset = idx3 % 32;
        if (0 == (bitMap_[index] & (1 << offset)))
        {
            return false;
        }

        return true;
    }
};

class BlackList
{
public:
    void add(string url)
    {
        blacklist_.setBit(url.c_str());
    }

    bool query(string url)
    {
        return blacklist_.getBit(url.c_str());
    }
private:
    BloomFilter blacklist_;
};

int main()
{
    BlackList list;
    list.add("http://www.baidu.com");
    list.add("http://www.360buy.com");
    list.add("http://www.tmall.com");
    list.add("http://www.tencent.com");

    string url = "http://www.alibaba.com";
    cout << list.query(url) << endl;
}