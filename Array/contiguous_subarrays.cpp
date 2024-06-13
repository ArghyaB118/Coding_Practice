/*
Contiguous Subarrays:

You are given an array arr of N integers. For each index i, 
you are required to determine the number of contiguous subarrays 
that fulfill the following conditions:
The value at index i must be the maximum element in the contiguous subarrays, and
These contiguous subarrays must either start from or end on index i.
Signature
int[] countSubarrays(int[] arr)

Input:
Array arr is a non-empty list of unique integers that range between 1 to 1,000,000,000
Size N is between 1 and 1,000,000
Output:
An array where each index i contains an integer denoting the maximum number 
of contiguous subarrays of arr[i].

Example:
arr = [3, 4, 1, 6, 2]
output = [1, 3, 1, 5, 1]
Explanation:
For index 0 - [3] is the only contiguous subarray that starts (or ends) with 3, 
and the maximum value in this subarray is 3.
For index 1 - [4], [3, 4], [4, 1]
For index 2 - [1]
For index 3 - [6], [6, 2], [1, 6], [4, 1, 6], [3, 4, 1, 6]
For index 4 - [2]
So, the answer for the above input is [1, 3, 1, 5, 1]
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> countSubarrays (vector<int> arr) {
	vector<int> num_subarrays;
	for (int i = 0; i < arr.size(); i++) {
		int count = 0;
		for (int j = i; j >= 0; j--) {
			if (arr[j] <= arr[i])
				count++;
			else
				break;
		}
		for (int j = i; j < arr.size(); j++) {
			if (arr[j] <= arr[i])
				count++;
			else
				break;
		}
		num_subarrays.push_back(count - 1);
	}
	return num_subarrays;
}

/* LC#689

Given an integer array nums and an integer k, 
find three non-overlapping subarrays 
of length k with maximum sum and return them.

Return the result as a list of indices 
representing the starting position 
of each interval (0-indexed). 
If there are multiple answers, 
return the lexicographically smallest one.
*/

vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
	int n = nums.size();
	vector<int> k_sum;
	int sum = 0;
	for (int i = 0; i < k; i++)
		sum += nums[i];
	k_sum.push_back(sum);
	for (int i = k; i < n; i++) {
		sum = sum - nums[i - k] + nums[i];
		k_sum.push_back(sum);
	}
	vector<int> k_sum_max_right(n - k + 1, 0);
	k_sum_max_right[n - k] = k_sum[n - k];
	for (int i = n - k - 1; i >= 0; i--)
		k_sum_max_right[i] = max(k_sum[i], k_sum_max_right[i + 1]);
	
	vector<int> max_two_sum(n - k + 1, 0);
	for (int i = 0; i < n - k + 1; i++)
		max_two_sum[i] = nums[i] + k_sum_max_right[i];

	vector<int> max_two_sum_right(n - k + 1, 0);
	max_two_sum_right[n - k] = max_two_sum[n - k];
	for (int i = n - k - 1; i >= 0; i--)
		max_two_sum_right[i] = max(max_two_sum[i], max_two_sum_right[i + 1]);

	int sum = 0;
	for (int i = 0; i < n - 2 * k + 1; i++) {
		sum = max(sum, nums[i] + max_two_sum_right[i + k]);
	}
	return sum;
}

int main () {
	vector<int> arr{3, 4, 1, 6, 2};
	arr = countSubarrays(arr);
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
	return 0;
}