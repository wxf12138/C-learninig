#include <iostream>
using namespace std;

int BinarySearch(int arr[], int i, int j, int val)
{
    if(i > j)
        return -1;
    int mid = (i + j) / 2;
    if(arr[mid] == val)
        return mid;
    else if(arr[mid] > val) 
    {
        BinarySearch(arr, i, mid - 1, val);
    }
    else
    {
        BinarySearch(arr, mid + 1, j, val);
    }
}
int BinarySearch(int arr[], int size, int val)
{
    return BinarySearch(arr, 0, size - 1, val);
    // int first = 0;
    // int last = size-1;

    // while(first <= last)
    // {
    //     int mid = first + last;
    //     if(arr[mid] == val)
    //     {
    //         return mid;
    //     }
    //     else if(arr[mid] > val)
    //     {
    //         last = mid - 1;
    //     }
    //     else
    //     {
    //         first = mid + 1;
    //     }
    // }
    // return -1;
}
int main()
{
    int arr[] = {12, 25, 34, 39, 45, 57, 63, 78, 82, 96, 100};
    int size = sizeof arr / sizeof arr[0];
    cout << BinarySearch(arr, size, 39) << endl;
    cout << BinarySearch(arr, size, 45) << endl;
    cout << BinarySearch(arr, size, 12) << endl;
    cout << BinarySearch(arr, size, 64) << endl;
}

// 二分搜索可以堪称一个bst树搜索过程，2^L - 1 = n
// L = logn   L为树的层数/高度 