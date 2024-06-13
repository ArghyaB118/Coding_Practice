#include <iostream>
#include <vector>
#include <experimental/iterator> // cpp 14
using namespace std;

// overloading `<<` operator
template <typename T> ostream& operator << (ostream& os, const vector<T>& v) {
	for (auto &e : v)
		os << e << " ";
	return os;	
}

// using a function
template <typename T>
void print (const vector<T>& v, string sep = " ") {
	for (auto &e : v)
		cout << e << sep;
	cout << endl;
}

template <typename T>
void print (const T* arr, int n, string sep = " ") {
	for (int i = 0; i < n; i++)
		cout << *arr + i << sep;
	cout << endl;
}


int increment (int x) { return x + 1; }

void reverse(vector<int>& v) {
	for (int i = 0, j = v.size() - 1; i < j; i++, j--) {
		swap(v[i], v[j]);
	}
}

template <typename T>
int CountTwos(const T& container) {
  return std::count_if(std::begin(container), std::end(container), [](int item) {
    return item == 2;
  });
}


int main () {
	vector<int> v = {1, 2, 3};
	// Topic 1: iterating through a vector
	for (auto &e : v)
		cout << e << " ";
	cout << endl;
	for (auto e : v)
		cout << e << " ";
	cout << endl;
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
	for (auto it = v.begin(); it != v.end(); it++)
		cout << *it << " ";
	cout << endl;

	// Topic 2: printing vector
	cout << v << endl;
	print(v, ", ");
	// print using stl algorithm copy
	copy(v.begin(), v.end(),
         ostream_iterator<int>(cout, " "));
	cout << endl;
	// print using experimental::make_ostream_joiner from C++17
	copy(v.begin(), v.end(),
         experimental::make_ostream_joiner(cout, " "));
	cout << endl;
	// using lambda statement from C++17
	for_each (v.begin(), v.end(), [](const auto& e) 
		{ cout << e << " "; });
	cout << endl;

	// Topic 3: converting an array to a vector
	int arr[] = {1, 2, 3, 4};
	int n = sizeof(arr) / sizeof(arr[0]);
	vector<int> v1;
	// naive way
	for (int i = 0; i < n; i++)
		v1.push_back(arr[i]);
	cout << v1 << endl;
	v1.clear();
	// second naive way, using pointer
	for (int i = 0; i < n; i++)
		v1.push_back(*(arr + i)); // or just v1.push_back(*arr + i);
	cout << v1 << endl;
	// range-based assignemnt on a newly-defined vector
	vector<int> v2(arr, arr + n);
	cout << v2 << endl;
	vector<int> v3(std::begin(arr), std::end(arr));
	cout << v3 << endl;
	// using vector insert
	v1.clear();
	v1.insert(v1.begin(), begin(arr), end(arr));
	cout << v1 << endl;
	v1.clear();
	// using copy
	copy(begin(arr), end(arr), back_inserter(v1));
	cout << v1 << endl; v1.clear();
	// using assign
	v1.assign(begin(arr), end(arr));
	cout << v1 << endl; v1.clear();
	// using transform
	transform(begin(arr), end(arr), back_inserter(v1), increment);
	cout << v1 << endl;

	// Topic 4: convering vector to array
	v = {1, 2, 3, 4, 5};
	n = v.size();
	int arr2[n];
	// naive approach
	for (int i = 0; i < n; i++)
		arr2[i] = v[i];
	print(arr2, n);
	// using copy
	copy(v.begin(), v.end(), arr2); print(arr2, n);
	// using transform
	transform(v.begin(), v.end(), arr2, [] (const int& x) { return x; });
	print(arr2, n);
	// using data without any auxiliary space
	int* arr3 = v.data(); print(arr3, n);
	// using reference without auxiliary space
	arr3 = &v[0]; print(arr3, n);

	//
	v = {4, 2, 6, 3, 1, 5}; cout << v << endl;
	sort(v.begin(), v.end()); cout << v << endl;
	reverse(v); cout << v << endl;

	vector<int> vv = std::move(v);
	cout << vv << endl;
	cout << v << endl;

	std::vector<int> arr4 = {2, 2, 43, 435, 4543, 534};
	int arr5[8] = {2, 43, 45, 435, 32, 32, 32, 32};
	auto a = CountTwos(arr4); // 2
	auto b = CountTwos(arr5);  // 1
	cout << a << " " << b << endl;
	return 0;
}
