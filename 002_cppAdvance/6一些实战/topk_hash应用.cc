#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
using namespace std;
/*
有一个大文件， 内存限制200m，求重复次数最多的前10个
大文件 ——》 小文件
大文件数据 -》 哈希映射 -》把离散的放入小文件当中
*/

int main()
{
    FILE *pf1 = fopen("./data.txt", "wb");
    for (int i = 0; i < 1000000; ++i)
    {
        int data = rand() % 100 + 1;
        fwrite(&data, sizeof(int), 1, pf1);
    }
    fclose(pf1); // 关闭文件，确保数据写入

    FILE *pf = fopen("./data.txt", "rb");
    if (pf == nullptr)
        return 0;
    const int FILE_NO = 11;
    FILE *pfile[FILE_NO] = {nullptr};
    ;

    // 创建小文件
    for (int i = 0; i < FILE_NO; ++i)
    {
        char file_name[256];
        sprintf(file_name, "./data_%d.txt", i + 1);
        pfile[i] = fopen(file_name, "wb");
    }

    // 哈希映射，把大文件数据映射到小文件当中
    int data;
    while (fread(&data, sizeof(int), 1, pf))
    {
        int hash_value = data % FILE_NO;
        fwrite(&data, sizeof(int), 1, pfile[hash_value]);
    }
    fclose(pf);

    // 关闭并重新打开小文件以进行读取
    /*
        写入数据时，数据先被写入缓冲区，再定期或在文件关闭时才会被刷新到磁盘上。
        为了确保数据全部写入到文件中，同时重置文件指针（例如从文件开头开始读取数据），
        你需要先关闭小文件，然后再以读模式（例如 "rb"）重新打开它们。这不仅保证了数据完整性，
        还能避免因文件缓冲和锁定导致的读取异常。
    */

    for (int i = 0; i < FILE_NO; ++i)

    {

        fclose(pfile[i]);

        char file_name[256];

        sprintf(file_name, "./data_%d.txt", i + 1);

        pfile[i] = fopen(file_name, "rb");

        if (pfile[i] == nullptr)

        {

            cerr << "无法打开文件 " << file_name << endl;

            return 1;
        }
    }

    // 定义一个链式哈希表
    unordered_map<int, int> numMap;

    // 先定义一个小根堆
    using P = pair<int, int>;
    using FUNC = function<bool(P &, P &)>;
    using MinHeap = priority_queue<P, vector<P>, FUNC>;
    MinHeap minHeap([](P &a, P &b)
                    { return a.second > b.second; });

    // 分段求解文件
    for (int i = 0; i < FILE_NO; ++i)
    {
        // 回复小文件指针到起始位置
        fseek(pfile[i], 0, SEEK_SET);

        while (fread(&data, sizeof(int), 1, pfile[i]))
        {
            numMap[data]++;
        }

        int k = 0;
        // 建一个10个元素的小根堆
        auto it = numMap.begin();
        if (minHeap.empty())
        {
            for (; it != numMap.end() && k < 10; ++it, ++k)
            {
                minHeap.push(*it);
            }
        }
        // 把 k + 1 个
        for (; it != numMap.end(); ++it)
        {
            if (it->second > minHeap.top().second)
            {
                minHeap.pop();
                minHeap.push(*it);
            }
        }
        numMap.clear();
    }

    // 关闭所有小文件
    for (int i = 0; i < FILE_NO; ++i)
    {
        fclose(pfile[i]);
    }

    while (!minHeap.empty())
    {
        auto it = minHeap.top();
        cout << it.first << ":" << it.second << endl;
        minHeap.pop();
    }
    return 0;
}