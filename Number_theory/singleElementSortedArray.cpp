/* LC#540

You are given a sorted array 
consisting of only integers 
where every element appears exactly twice, 
except for one element 
which appears exactly once.

Return the single element 
that appears only once.

Your solution must run in 
O(log n) time and O(1) space.
*/

// beats ~76% LC users
int singleNonDuplicate(vector<int>& nums) {
	if (nums.size() == 1)
		return nums[0];
	int left = 0, right = nums.size() - 1;
	while (left <= right) {
		if (left == right)
			return nums[left];
		int mid = (left + right) / 2;
		if ((mid - left + 1) % 2 != 0)
			mid -= 1;
		if (nums[mid] == nums[mid - 1])
			left = mid + 1;
		else if (nums[mid] == nums[mid + 1])
			right = mid - 1;
		else
			return nums[mid];
	}
	return -1;
}