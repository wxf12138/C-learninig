#include <iostream>
#include <cstring>
#include <random>
#include <ctime>
using namespace std;

// 逆序字符串
void reverse(char arr[], int size)
{
    char *p = arr;
    char *q = arr + size - 1;
    while (p < q)
    {
        char temp = *p;
        *p = *q;
        *q = temp;
        p++;
        q--;
    }
}
int main()
{
    char arr[] = "abcdefg";
    reverse(arr, strlen(arr));
    cout << arr << endl;
}