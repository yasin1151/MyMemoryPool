#include "../MyMemoryPool.hpp"

#include <iostream>
using namespace std;

int main()
{
	MyMemoryPool<int> Demo(3);


	int* ptr1 = Demo.Alloc();
	int* ptr2 = Demo.Alloc();
	int* ptr3 = Demo.Alloc();

	cout << "ptr 1:" << ptr1 << endl
		<< "ptr 2:" << ptr2 << endl
		<< "ptr 3:" << ptr3 << endl;

	Demo.Delete(ptr2);
	int* ptr4 = Demo.Alloc();
	cout << "ptr 4:" << ptr4 << endl;

	system("pause");
	return 0;
}