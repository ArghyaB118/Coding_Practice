/* LC#503

Given a circular integer array nums 
(i.e., the next element of nums[nums.length - 1] is nums[0]), 
return the next greater number for every element in nums.

The next greater number of a number x is 
the first greater number to its traversing-order 
next in the array, 
which means you could search circularly 
to find its next greater number. 
If it doesn't exist, return -1 for this number.
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// beats ~10% LC users
vector<int> nextGreaterElements(vector<int>& nums) {
	int n = nums.size();
	vector<int> ans(n, -1);
	for (int i = 0; i < n; i++) {
		int idx = i + 1;
		while (idx % n != i) {
			if (nums[idx % n] > nums[i]) {
				ans[i] = nums[idx % n];
				break;
			}
			idx++;
		}
	}
	return ans;
}


// beats ~75% LC users
vector<int> nextGreaterElementsOpt(vector<int>& nums) {
	stack<int> st;
	int n = nums.size();
	vector<int> ans(n, -1);
	for (int i = 0; i < 2; i++) {
		for (int j = n - 1; j >= 0; j--) {
			//if (ans[j] != -1) {
				if (st.empty())
					st.push(j);
				else {
					while (!st.empty()) {
						if (nums[st.top()] > nums[j]) {
							ans[j] = nums[st.top()];
							break;
						}
						else
							st.pop();
					}
					st.push(j);
				}
			//}
		}
	}
	return ans;
}

int main () {
	vector<int> nums = {1, 2, 1};
	vector<int> ans = nextGreaterElementsOpt(nums);
	for (int &i : ans)
		cout << i << " ";
	cout << endl;
	return 0;
}