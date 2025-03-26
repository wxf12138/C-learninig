#include <iostream>
using namespace std;

void *operator new(size_t size)
{
	void *p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << "operator new addr: " << p << endl;
	return p;
}

void *operator new[](size_t size)
{
	void *p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << "operator new[] addr: " << p << endl;
	return p;
}

void operator delete(void *ptr)
{
	cout << "operator delete addr: " << ptr << endl;
	free(ptr);
}

void operator delete[](void *ptr)
{
	cout << "operator delete[] addr: " << ptr << endl;
	free(ptr);
}

class Test
{
public:
	Test(int data = 10) { cout << "Test()" << endl; }
	~Test() { cout << "~Test()" << endl; }

private:
	int ptr;
};

int main()
{
	// 空指针operator delete[] addr: 0x55ea47c20ea8
	// free(): invalid pointer
	//  Test* p1 = new Test();
	//  cout << "p1: "<< p1 << endl;
	//  delete []p1;
	// munmap_chunk(): invalid pointer
	// Aborted (core dumped)

	// Test* p2 = new Test[10];
	// cout << "p2: "<< p2 << endl;
	// delete []p2;
	//munmap_chunk(): invalid pointer
	Test *p3 = new Test[10];
	cout << "p3: " << p3 << endl;
	delete p3;

}