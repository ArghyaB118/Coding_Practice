#include <iostream>
using namespace std;

void display(int arr[], int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}


bool beautiful(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		if (arr[i] > (i+1) && arr[i] % (i+1) != 0)
			return false;
		else if ((i+1) > arr[i] && (i+1) % arr[i] != 0)
			return false;
	}
	return true;
}

int main() {
	int n = 5, count = 0;
	// method 1: create the permutations
	// check if they are beautiful or not
	// increase the counter 
	int a[n];
	for (int i = 0; i < n; i++)
		a[i] = i + 1;
	do {
		//display(a, n);
		if (beautiful(a, n))
			count++;
	}  while (next_permutation(a, a + n));
	cout << count << endl;
	return 0;
}