#include <iostream>
using namespace std;

void print (int* arr, int n) {
	for (int i = 0; i < n; i++)
		cout << *(arr + i) << " ";
	cout << endl;
}

int increment(int x) { return x + 1; }

// a class that acts as a functor
class increment2{
private:
	int num;
public:
	increment2(int n) : num(n) {}
	int operator () (int num_) const {
		return num + num_;
	}
};

int main () {
	int arr[] = {1, 2, 3};
	int n = 3;
	print (arr, n);
	transform(arr, arr + n, arr, increment);
	print (arr, n);
	transform(arr, arr + n, arr, increment2(2));
	print(arr, n);
	return 0;
}