#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int partation(int array[], int left, int right)
{
    // 选择基准数的优化：“三数取中”法   arr[l]   arr[r]   arr[(l+r)/2]  
	// 记录基准数
    int val = array[left];
    // 一次快排处理   时间：O(n) * O(logn) = O(nlogn)    空间：O(logn) 递归的深度所占用的栈内
    while (left < right)
    {
        while (left < right && array[right] >= val) // 从右向左找到首个小于基准数的元素
            right--;
        if (left < right)
            array[left++] = array[right]; // 与left交换，left++

        while (left < right && array[left] < val)
            left++;
        if (left < right)
            array[right--] = array[left];
    }
    array[left] = val;
    return left;
}

void QuickSort(int array[], int left, int right)
{
    if (left >= right)
    {
        return;
    }
    // 优化一：当[begin, end]序列的元素个数小到指定数量，采用插入排序
    // if (end - begin <= 50)
    //{ 
    // InsertSort(arr, begin, end);
    // return;
    //}

    // 在[begin, end]区间的元素做一次快排分割处理
    int pos = partation(array, left, right);
    QuickSort(array, left, pos - 1);
    QuickSort(array, pos + 1, right);
}

// 快速排序
void QuickSort(int array[], int size)
{
    return QuickSort(array, 0, size - 1);
}

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

    QuickSort(arr, 10);

    for (int var : arr)
    {
        cout << var << " ";
    }
    cout << endl;
}