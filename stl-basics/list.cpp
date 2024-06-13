#include <iostream>
#include <list>
using namespace std;

template <typename T>
void print (list<T>& l) {
	for (auto &e : l)
		cout << e << " ";
	cout << endl;
}

template <typename T>
void print2 (list<T>& l) {
	for (std::list<int>::iterator it = l.begin(); it != l.end(); it++)
		cout << *it << " ";
	cout << endl;
}

// strong auto parameter and decltype in cpp11
template <typename X, typename Y>
auto add (X x, Y y) -> decltype(x + y) { return x + y; }


int main () {
	list<int> l1 (4, 1); print(l1);
	int arr[3] = {1, 2, 3};
	list<int> l2 (std::begin(arr), std::end(arr)); print(l2);
	list<int> l3 (arr, arr + sizeof(arr) / sizeof(arr[0])); print(l3);

	cout << add (1, 2.3) << endl;
	return 0;
}