#include <iostream>

#include <memory> // for unique_ptr
using namespace std;

int main () {
	int x = 62;
	cout << x << " " <<  &x << endl;
	// The pointer is allocated on the stack, 
	// but what it points to is on the heap.
	int* y = new int(6);
	cout << y << " " << *y << " " << &y << endl;
	int* z = &x;
	cout << z << " " << *z << " " << &z << endl;
	delete z; // manual deallocation

	// recommended way from cpp14
	std::unique_ptr<int> ptr = std::make_unique<int>(42);
	cout << ptr << " " << *ptr << " " << &ptr << endl;
	// memory automatically deallocated as ptr goes out of scope.
	return 0;
}