#include <iostream>
#include <cstring>
#include <random>
#include <ctime>
using namespace std;

class Array
{
public:
    Array(int size = 10) : mpSize(size), mpCur(0)
    {
        mpArr = new int[mpSize]();
    }
    ~Array()
    {
        delete[] mpArr;
        mpArr = nullptr;
    }

public:
    void pop_back()
    {
        if (mpCur == 0)
        {
            return;
        }
        else
        {
            mpCur--;
        }
    }
    void push_back(int val)
    {
        if (mpCur == mpSize)
        {
            expand(2 * mpSize);
        }
        mpArr[mpCur++] = val;
    }
    void insert(int pos, int val)
    {
        if (pos < 0 || pos > mpCur)
        {
            return;
        }
        if (mpCur == mpSize)
        {
            expand(2 * mpSize);
        }
        for (int i = mpCur - 1; i >= pos; i--)
        {
            mpArr[i + 1] = mpArr[i];
        }
        mpArr[pos] = val;
        mpCur++;
    }
    void erase(int pos)
    {
        if (pos < 0 || pos >= mpCur)
        {
            return;
        }
        for (int i = pos; i < mpCur - 1; i++)
        {
            mpArr[i] = mpArr[i + 1];
        }
        mpCur--;
    }
    int find(int val)
    {
        for (int i = 0; i < mpCur; i++)
        {
            if (mpArr[i] == val)
            {
                cout << i << endl;
            }
        }
        return -1;
    }

private:
    friend ostream &operator<<(ostream &os, Array &arr);
    void expand(int size)
    {
        int *pArr = new int[size];
        memcpy(pArr, mpArr, sizeof(int) * mpCur);
        delete[] mpArr;

        mpArr = pArr;
        mpSize = size;
    }

    int *mpArr;
    int mpSize;
    int mpCur;
};
ostream &operator<<(ostream &os, Array &arr)
{
    os << "[";
    for (int i = 0; i < arr.mpCur; i++)
    {
        if (i == arr.mpCur - 1)
        {
            os << arr.mpArr[i];
        }
        else
        {
            os << arr.mpArr[i] << ",";
        }
    }
    os << "]" << endl;
    return os;
}

int main()
{
    Array arr;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        arr.push_back(rand() % 100);
    }
    cout << arr;
    arr.pop_back();
    cout << arr;
}