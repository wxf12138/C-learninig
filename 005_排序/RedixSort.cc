#include <iostream>
#include <time.h>
#include <string>
#include <vector>
using namespace std;

// 基数排序 适用于数据量较大但数据范围较小的情况
void RadixSort(int arr[], int size)
{
    // 选择最大元素 取其位数
    int maxData = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (maxData < abs(arr[i]))
        {
            maxData = abs(arr[i]);
        }
    }

    int len = to_string(maxData).size();

    vector<vector<int>> vecs;
    int mod = 10;
    int dev = 1;
    
    for (int i = 0; i < len; mod *= 10, dev *= 10, i++)
    {
        vecs.resize(20);

        for (int j = 0; j < size; j++)
        {
            // 数组中第i各位置的数字
            int index = arr[j] % mod / dev + 10;
            vecs[index].push_back(arr[j]);
        }

        // 依次遍历所有桶，把元素拷贝回原来数组当中
        int idx = 0;
        for (auto vec : vecs)
        {
            for (auto v : vec)
            {
                arr[idx++] = v;
            }
        }
        vecs.clear();
    }
}

int main()
{
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100 + 1;
	}

	arr[9] = -123;
	arr[6] = -38;

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	RadixSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}