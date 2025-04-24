#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 堆得下沉操作
void siftdown(int arr[], int i, int size)
{
    int val = arr[i];
	while (i < size / 2)
	{
		int child = 2 * i + 1;
		if (child + 1 < size && arr[child + 1] > arr[child])
		{
			child = child + 1;
		}

		if (arr[child] > val)
		{
			arr[i] = arr[child];
			i = child;  // i继续指向它的孩子，继续调整
		}
		else
		{
			break;
		}
	}
	arr[i] = val;
}
void HeapSort(int arr[], int size)
{
    int n = size - 1;
        // 第一个非叶子节点
    for (int i = (n - 1) / 2; i >= 0; i--)
    {
        siftdown(arr, i, size);
    }

    // 把堆顶元素和末尾元素交换 从对顶开始下沉操作
    for (int i = n; i > 0; i--)
    {
        // 出堆 首位元素互换
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        siftdown(arr, 0, i);
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

    for (int var : arr)
    {
        cout << var << " ";
    }
    cout << endl;

    HeapSort(arr, 10);

    for (int var : arr)
    {
        cout << var << " ";
    }
    cout << endl;
}