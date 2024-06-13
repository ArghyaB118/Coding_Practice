/* LC#53

Given an integer array nums, 
find the contiguous subarray (containing at least one number) 
which has the largest sum and return its sum.
 
A subarray is a contiguous part of an array.
*/


#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

// beats ~100% LC users
int maxSubArray(vector<int>& nums) {
    if (nums.size() == 0)
        return 0;
    if (nums.size() == 1)
        return nums[0];
    int ans = INT_MIN, sum = 0; // kadane's algorithm
    // as I don't use an int to iterate, it's better
    for (std::vector<int>::iterator i = nums.begin(); 
        i != nums.end(); ++i) {
        sum += *i; // pointer to variable
        if (sum > ans)
            ans = sum;
        if (sum < 0)
            sum = 0;
    }
    return ans;
}

int maxSubArrayDCUtil (vector<int>& nums, int l, int r) {
    if (l > r)
        return INT_MIN;
    else if (l == r)
        return nums[l];
    else if (r - l == 1 && nums[l] > 0 && nums[r] > 0)
        return nums[l] + nums[r];
    else if (r - l == 1)
        return max(nums[l], nums[r]);

    int mid = (l + r) / 2;
    int x = maxSubArrayDCUtil(nums, l, mid - 1);
    int y = maxSubArrayDCUtil(nums, mid + 1, r);
    
    int leftsum = 0, rightsum = 0;
    for (int i = mid - 1; i >= l; i--)
        leftsum += nums[i];
    
    for (int i = mid + 1; i <= r; i++)
        rightsum += nums[i];
    
    int z = leftsum + nums[mid] + rightsum;
    return (x > y) ? max(x, z) : max(y, z);
}

int maxSubArrayDC (vector<int>& nums) {
    return maxSubArrayDC(nums, 0, nums.size() - 1);
}

/* LC#643

You are given an integer array nums 
consisting of n elements, and an integer k.

Find a contiguous subarray whose length is equal to k 
that has the maximum average value 
and return this value. 
Any answer with a calculation error 
less than 10^-5 will be accepted.
*/

double findMaxAverage(vector<int>& nums, int k) {
    double sum = accumulate(nums.begin(), nums.begin() + k, 0);
    double ans = sum / k;
    if (k == nums.size())
        return ans;
    for (int i = k; i < nums.size(); i++) {
        sum -= nums[i - k];
        sum += nums[i];
        ans = max(ans, sum / k);
    }
    return ans;
}

int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << maxSubArray(nums) << endl;
    return 0;
}
