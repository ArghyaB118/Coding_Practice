#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
using namespace std;

int main () {
	vector<int> nums= {3, 1, 5, 7, 8};
	vector<int> filtered(nums.size());
	std::ranges::sort(nums);
	for (auto& i : nums)
		cout << i << " ";
	cout << endl;

	auto it = std::copy_if(nums.begin(), 
		nums.end(), 
		filtered.begin(), 
		[](int num) { return num > 3; }); 
	
	filtered.resize(std::distance(filtered.begin(), it));
	for (auto& i : filtered)
		cout << i << " ";
	cout << endl;

	// std::ranges::copy_if does the same except returning the
	// iterator to the end.
	// on the other hand, not initiating filtered throws error.
	// workaround
	vector<int> filtered2;
	std::copy_if(nums.begin(), 
		nums.end(), 
		back_inserter(filtered2), 
		[](int num) { return num > 3; });
	for (auto& i : filtered2)
		cout << i << " ";
	cout << endl;

	std::ranges::transform(filtered, 
		filtered.begin(), 
		[](int i) { return i * i; });
	for (auto& i : filtered)
		cout << i << " ";
	cout << endl;
	return 0;
}