#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 冒泡排序
// 效率较低，原因是交换次数过多
void BubbleSort(int arr[], int size)
{
    // 趟数  O(n) * O(n) = O(n^2)
    for (int i = 0; i < size - 1; i++) // 就剩最后一个数字的时候不用排序，故size - 1
    {
        bool flag = false;
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = true;
            }
        }

        if (!flag)
        {
            // 如果没有做任何的数据交换，那么说明数据已经有序了
            return;
        }
    }
}

// 选择排序 比较多，相较于冒泡交换较少
void ChoiceSort(int arr[], int size)
{
    // 外循环：未排序区间为 [i, n-1]
    for (int i = 0; i < size - 1; i++)
    {
        int min = arr[i];
        int k = i;// 记录最小元素下标
        // 内循环：找到未排序区间内的最小元素 
        for (int j = i + 1; j < size; j++)
        {
            // 记录交换的值及下标
            if (arr[j] < min)
            {
                min = arr[j];
                k = j;
            }
        }
        // 找到后面序列中的最小值和开始位置交换
        if (k != i)
        {
            int tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp;
        }
    }
}

// 插入排序，如果数据趋于有序，那么插入排序是所有排序算法中，
/* 在基础排序算法中，
插入排序 > 冒泡排序&选择排序
效率最高的排序算法!
不仅仅没有交换，而且比较的次数也少! */
void InsertSort(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int val = arr[i];//记录val值
        int j = i - 1;
        while (j >= 0 && arr[j] > val)
        {
            arr[j + 1] = arr[j]; // 将 arr[j] 向右移动一位
            j--;
        }
        arr[j + 1] = val; // 将val赋值到正确位置（找到第一个arr[j] <= val 的位置为j， j+1为要添加的位置）
    }
}

// 希尔排序

void HillSort(int arr[], int size)
{
    for (int gap = size / 2; gap > 0; gap = gap / 2)
    {
        for (int i = gap; i < size; i++)
        {
            int val = arr[i];
            int j = i - gap;
            while (j >= 0 && arr[j] > val)
            {
                arr[j + gap] = arr[j];
                j = j - gap;
            }
            arr[j + gap] = val;
        }
    }
}
#if 0
int main()
{
    int arr[10];
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 100 + 1;
    }

    for (int var : arr)
    {
        cout << var << " ";
    }
    cout << endl;

    HillSort(arr, 10);

    for (int var : arr)
    {
        cout << var << " ";
    }
    cout << endl;
}
#endif

int main()
{
	const int COUNT = 10000;
	int* arr = new int[COUNT];
	int* brr = new int[COUNT];
	int* crr = new int[COUNT];
	int* drr = new int[COUNT];

	srand(time(NULL));

	for (int i = 0; i < COUNT; i++)
	{
		int val = rand() % COUNT;
		arr[i] = val;
		brr[i] = val;
		crr[i] = val;
		drr[i] = val;
	}

	clock_t begin, end;

	begin = clock();
	BubbleSort(arr, COUNT);
	end = clock();
	cout << "BubbleSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	ChoiceSort(brr, COUNT);
	end = clock();
	cout << "ChoiceSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	InsertSort(crr, COUNT);
	end = clock();
	cout << "InsertSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	begin = clock();
	HillSort(drr, COUNT);
	end = clock();
	cout << "ShellSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
}