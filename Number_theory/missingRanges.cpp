/* LC#163

You are given an inclusive range [lower, upper] 
and a sorted unique integer array nums, 
where all elements are within the inclusive range.

A number x is considered missing if 
x is in the range [lower, upper] and x is not in nums.

Return the shortest sorted list of ranges 
that exactly covers all the missing numbers. 
That is, no element of nums is included 
in any of the ranges, 
and each missing number is covered by one of the ranges.
*/

// beats ~40% LC users
vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
	if (nums.size() == 0)
        return {{lower, upper}};
    if (nums.size() == 1) {
    	if (nums[0] == lower && lower < upper)
    		return {{lower + 1, upper}};
    	else if ((nums[0] == lower || nums[0] == upper) && lower == upper)
    		return {};
    	else if (nums[0] == upper && lower < upper)
    		return {{lower, upper - 1}};
    	else {
    		return {{lower, nums[0] - 1}, {nums[0] + 1, upper}};
    	}
    }
	vector<vector<int>> missing_ranges;
	if (nums[0] > lower)
		missing_ranges.push_back({lower, nums[0] - 1});
	for (int i = 1; i < nums.size(); i++) {
		if (nums[i] != nums[i - 1] + 1)
			missing_ranges.push_back({nums[i - 1] + 1, nums[i] - 1});
	}
	if (nums.back() < upper)
		missing_ranges.push_back({nums.back() + 1, upper});
	return missing_ranges;
}