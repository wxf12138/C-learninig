#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
/*
海量数据查重问题
1.哈希表
2.分治思想
3.布隆过滤器
4.字符串类型 字典树（前缀树）
*/
// 1.哈希表
#if 0
int main()
{
    const int SIZE = 1000000;
    int arr[SIZE] = {0};

    for (int i = 0; i < SIZE; ++i)
    {
        arr[i] = rand();
    }

    //在arr找出重复的元素，并统计次数
    std::unordered_map<int, int> map;
    for (int val : arr)
    {
        map[val]++;
    }

    for (auto pair : map)
    {
        if(pair.second > 1)
        {
            std::cout << pair.first << " " << pair.second << std::endl; 
        }
    }
    return 0;
}
#endif

/*
	a,b两个文件，里面都有10亿个整数，内存限制400M，让你求出a，b两个文件当中重复的元素有哪些？
	10亿 -》 全部读取内存中，1G*4*2=8G/400M = 27个小文件
	a =》 全部读到内存当中，存储到哈希表
	b =》 从b文件读数据，在内存哈希表中查询

	把a和b两个大文件，划分成个数相等的一系列（27）小文件（分治思想）
	从a文件中读取数据，通过 数据%27=file_index
	从b文件中读取数据，通过 数据%27=file_index

	a和b两个文件中，数据相同的元素，进行哈希映射以后肯定在相同序号的小文件当中
	
	*/

/*
    有一个文件，有大量的整数 50亿个整数，内存限制400M，让你找出文件中重复的元素，重复次数
	哈希表：50亿=5G*4=20G, 20G*2=40G内存
	分治法的思想：大文件划分成小文件，使得每一个小文件能够加载到内存当中，求出对应的重复元素
	大文件 =》 小文件的个数（40G / 400M = 120个小文件）
	data0.txt
	data1.txt
	data2.txt
	...
	data126.txt
	遍历大文件的元素，把每一个元素根据哈希映射函数，放到对应序号的小文件当中
	data % 127 = file_index
	值相同的，通过一样的哈希映射函数，肯定是放在同一个小文件当中的
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstdlib> // abs
#include <string>

using namespace std;

const int NUM_PARTS = 127;

// 分割文件，将大文件中的整数根据 hash 映射到多个小文件中
void partitionFile(const string &inputFilename, const string &outputPrefix)
{
    ifstream inFile(inputFilename, ios::binary);
    if (!inFile)
    {
        cerr << "Error opening input file: " << inputFilename << endl;
        exit(EXIT_FAILURE);
    }

    // 创建 NUM_PARTS 个输出文件流
    vector<ofstream> outFiles;
    outFiles.reserve(NUM_PARTS);
    for (int i = 0; i < NUM_PARTS; i++)
    {
        string outFilename = outputPrefix + "_part_" + to_string(i) + ".dat";
        outFiles.emplace_back(outFilename, ios::binary);
        if (!outFiles.back())
        {
            cerr << "Error opening output file: " << outFilename << endl;
            exit(EXIT_FAILURE);
        }
    }

    int num;
    // 逐个读取整数并写入对应的小文件
    while (inFile.read(reinterpret_cast<char *>(&num), sizeof(num)))
    {
        int index = abs(num) % NUM_PARTS; // 映射到 0 ~ NUM_PARTS-1
        outFiles[index].write(reinterpret_cast<const char *>(&num), sizeof(num));
    }

    inFile.close();
    for (int i = 0; i < NUM_PARTS; i++)
    {
        outFiles[i].close();
    }
}

// 处理单个分片文件，统计重复数字及其出现次数并输出
void processPartition(int partIndex, const string &prefix)
{
    string filename = prefix + "_part_" + to_string(partIndex) + ".dat";
    ifstream inFile(filename, ios::binary);
    if (!inFile)
    {
        cerr << "Error opening partition file: " << filename << endl;
        return;
    }

    // 使用unordered_map统计每个数字的出现次数
    unordered_map<int, long long> countMap;
    int num;
    while (inFile.read(reinterpret_cast<char *>(&num), sizeof(num)))
    {
        countMap[num]++;
    }
    inFile.close();

    // 输出出现次数大于1的数字
    for (const auto &entry : countMap)
    {
        if (entry.second > 1)
        {
            cout << "Number " << entry.first << " appears " << entry.second
                 << " times in partition " << partIndex << endl;
        }
    }
}

int main()
{
    string inputFile = "data.dat"; // 原始大文件
    string outputPrefix = "data";  // 分割后的小文件前缀

    // 1. 分割大文件
    partitionFile(inputFile, outputPrefix);

    // 2. 对每个分片处理，统计重复的数字
    for (int i = 0; i < NUM_PARTS; i++)
    {
        processPartition(i, outputPrefix);
    }

    return 0;
}
