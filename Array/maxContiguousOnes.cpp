/* LC#1004

Given a binary array nums and an integer k, 
return the maximum number of consecutive 1's 
in the array if you can flip at most k 0's.
*/

#include <iostream>
#include <vector>
using namespace std;

// Idea: use sliding window
// try to find a max window with <= k zeros
// beats ~82% LC users
int longestOnes(vector<int>& nums, int k) {
	int left = 0, right = 0;
	int result = 0;
	while (right < nums.size()) {
		cout << left << " " << right << endl;
		if (k > 0 && nums[right] == 0) {
			k--; right++;
		}
		else if (k > 0 && nums[right] == 1)
			right++;
		else if (k == 0 && nums[right] == 1)
			right++;
		else if (k == 0 && nums[right] == 0) {
			result = max(result, right - left);
			if (nums[left] == 0)
				k++;
			left++;
		}
	}
	result = max(result, right - left);
	return result;
}

int main () {
	vector<int> nums = {1,1,1,0,0,0,1,1,1,1,0};
	cout << longestOnes(nums, 2) << endl;
	return 0;
}