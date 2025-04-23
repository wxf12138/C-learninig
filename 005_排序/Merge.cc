#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 归并排序

// 归并过程函数
void merge(int arr[], int left, int mid, int right)
{
    // 左子数组区间为 [left, mid], 右子数组区间为 [mid+1, right]
    // 创建一个临时数组 tmp ，用于存放合并后的结果
    int *p = new int[right - left + 1];
    int i = left;
    int j = mid + 1;
    int k = 0; // 用于存储新的数组的下标
               // 当左右子数组都还有元素时，进行比较并将较小的元素复制到临时数组中
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            p[k++] = arr[i++];
        }
        else
        {
            p[k++] = arr[j++];
        }
    }
    // 将左子数组和右子数组的剩余元素复制到临时数组中
    while (i <= mid)
    {
        p[k++] = arr[i++];
    }
    while (j <= right)
    {
        p[k++] = arr[j++];
    }
    // 将临时数组 tmp 中的元素复制回原数组 nums 的对应区间
    for (k = 0; k < right - left + 1; k++)
    {
        arr[left + k] = p[k];
    }

    delete []p;
}

void MergeSort(int arr[], int left, int right)
{
    // 终止条件
    if (left >= right)
        return; // 当子数组长度为 1 时终止递归
    // 划分阶段
    int mid = left + (right - left) / 2; // 计算中点
    MergeSort(arr, left, mid);           // 递归左子数组
    MergeSort(arr, mid + 1, right);      // 递归右子数组
    // 合并阶段
    merge(arr, left, mid, right);
}

void MergeSort(int arr[], int size)
{
    MergeSort(arr, 0, size - 1);
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

    MergeSort(arr, 10);

    for (int var : arr)
    {
        cout << var << " ";
    }
    cout << endl;
}