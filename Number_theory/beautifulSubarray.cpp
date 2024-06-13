/* LC#2461

You are given an integer array nums and an integer k. 
Find the maximum subarray sum of 
all the subarrays of nums that meet the following conditions:

The length of the subarray is k, and
All the elements of the subarray are distinct.
Return the maximum subarray sum 
of all the subarrays that meet the conditions. 
If no subarray meets the conditions, return 0.

A subarray is a contiguous non-empty sequence 
of elements within an array.

1 <= k <= nums.length <= 10^5
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// TLE
long long maximumSubarraySum2(vector<int>& nums, int k) {
    long long sum = 0;
    unordered_map<int, int> elts;
    for (int i = 0; i < k; i++) {
        if (elts.find(nums[i]) == elts.end())
            elts.insert({nums[i], 1});
        else
            elts[nums[i]]++;
    }
    if (elts.size() == k) {
        long long tmp = 0;
        for (auto &j : elts)
            tmp += j.first;
        sum = (sum < tmp) ? tmp : sum;
    }
    int i = k;
    while (i < nums.size()) {      
        if (elts[nums[i - k]] > 1)
            elts[nums[i - k]]--;
        else
            elts.erase(nums[i - k]);
        
        if (elts.find(nums[i]) == elts.end())
            elts[nums[i]] = 1;
        else
            elts[nums[i]]++;

        if (elts.size() == k) {
            long long tmp = 0;
            for (auto &j : elts)
                tmp += j.first;
            sum = (sum < tmp) ? tmp : sum;
        }
        i++;
    }
    return sum;
}

// beats ~58% LC users
long long maximumSubarraySum(vector<int>& nums, int k) {
    long long sum = 0, tmp = 0;
    unordered_map<int, int> elts;
    for (int i = 0; i < nums.size(); i++) {
        if (i >= k) {
            tmp -= nums[i - k];
            if (--elts[nums[i - k]] == 0)
                elts.erase(nums[i - k]);
        }
        tmp += nums[i];
        elts[nums[i]]++;
        if (elts.size() == k)
            sum = max(sum, tmp);
    }
    return sum;
}

int main () {
        vector<int> nums = {1,5,4,2,9,9,9};
        int k = 3;
        cout << maximumSubarraySum(nums, k) << endl;
        return 0;
}