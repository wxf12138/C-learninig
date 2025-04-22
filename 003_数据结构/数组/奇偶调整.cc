#include <iostream>
#include <cstring>
#include <random>
#include <ctime>

using namespace std;

void oddEvenSort(int arr[], int n)
{
    int* p = arr;          // 指向数组起始位置
    int* q = arr + n - 1;  // 指向数组末尾
    while (p < q)
    {
        // 找到第一个奇数
        while (p < q && (*p % 2) == 0)
            ++p;

        // 找到最后一个偶数
        while (p < q && (*q % 2) == 1)
            --q;

        // 交换奇偶数
        if (p < q) {
            std::swap(*p, *q); 
            ++p;
            --q;
        }
    }
}

int main()
{
    srand(time(NULL));
    int arr[10];
    for (int i = 0; i < 10; ++i)
    {
        arr[i] = rand() % 100;
    }

    for (int val : arr)
    {
        std::cout << val << " ";
    }
    std::cout << endl;
    
    oddEvenSort(arr, 10);
    for (int val : arr)
    {
        std::cout << val << " ";
    }
    std::cout << endl;
}