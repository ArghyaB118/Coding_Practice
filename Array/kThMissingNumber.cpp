/* LC#1539

Given an array arr of positive integers sorted 
in a strictly increasing order, and an integer k.

Return the kth positive integer 
that is missing from this array.

Follow up:

Could you solve this problem 
in less than O(n) complexity?
*/

#include <iostream>
#include <vector>
using namespace std;

int findKthPositive(vector<int>& arr, int k) {
	if (arr.size() - arr.back() < k)
		return arr.back() + (k - (arr.size() - arr.back()));
	else if (arr[0] > k)
		return k;

	k -= (arr[0] - 1);
	for (int i = 1; i < arr.size(); i++) {
		if (arr[i] == arr[i - 1] + 1)
			continue;
		else
			k -= (arr[i] - arr[i - 1] - 1);
		if (k <= 0)
			return arr[i] - 1 + k;
	}

	return arr.back() + k;
}

int findKthPositive2(vector<int>& arr, int k) {
	if (arr.size() - arr.back() < k)
		return arr.back() + (k - (arr.size() - arr.back()));
	else if (arr[0] > k)
		return k;

	int left = 0, right = arr.size();
	while (left < right) {
		int mid = (left + right) / 2;
		if (right - left == 1) {
			if (arr[left] - left - 1 == k)
				return arr[left] - 1;
			else if (arr[left] - left - 1 > k) {
				return arr[left] - ((arr[left] - left - 1) - k);
			}
			else if (arr[right] - right - 1 == k)
				return arr[right] - 1;
			else if (arr[right] - right - 1 > k) {
				return arr[right] - ((arr[right] - right - 1) - k);
			}
		}
		if (arr[mid] - mid - 1 > k)
			right = mid;
		else
			left = mid;
	}
    return -1;
}


/* LC#1060

Given an integer array nums 
which is sorted in ascending order 
and all of its elements are unique 
and given also an integer k, 
return the kth missing number 
starting from the leftmost number of the array.

Constraints:

1 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 10^7
nums is sorted in ascending order, 
and all the elements are unique.
1 <= k <= 10^8
*/

// beats ~86% LC users
int missingElement(vector<int>& nums, int k) {
	if (nums.size() == 1)
		return nums[0] + k;
	if (nums.back() - nums[0] + 1 - nums.size() < k)
		return nums.back() + (k - (nums.back() - nums[0] + 1 - nums.size()));
	
	for (int i = 1; i < nums.size(); i++) {
		k -= (nums[i] - nums[i - 1] - 1);
		if (k <= 0)
			return nums[i] + k - 1;
	}

	return -1;
}

/* LC#378

Given an n x n matrix 
where each of the rows and columns 
is sorted in ascending order, 
return the kth smallest element in the matrix.

Note that it is the kth smallest element 
in the sorted order, 
not the kth distinct element.

You must find a solution 
with a memory complexity better than O(n^2).
*/

int kthSmallestNaive(vector<vector<int>>& matrix, int k) {
    vector<int> arr;
    for (auto &i : matrix)
        for (auto &j : i)
            arr.push_back(j);
    sort(arr.begin(), arr.end());
    return arr[k - 1];
}

struct elt {
	int row, col, val;
	elt (int row_, int col_, int val_) {
		row = row_; col = col_; val = val_;
	};
};

struct cmp {
	bool operator() (const elt &e1, const elt &e2) {
		return e1.val > e2.val;
	};
};

int kthSmallest(vector<vector<int>>& matrix, int k) {
	int n = matrix.size();
	int count = 0;
	priority_queue<elt, vector<elt>, cmp> pq;
    for (int i = 0; i < n; i++) {
        elt e(i, 0, matrix[i][0]);
    	pq.push(e);
    }
    while (count < k - 1) {
    	elt e = pq.top();
    	pq.pop(); count++;
    	if (e.col < n - 1) {
            elt ee(e.row, e.col + 1, matrix[e.row][e.col + 1]);
    		pq.push(ee);
        }
    }
    return pq.top().val;
}

int main () {
	vector<int> nums = {4,5,7};
	cout << missingElement(nums, 2) << endl;
	return 0;
}