/* #LC#18
 
 Given an array nums of n integers, 
 return an array of all the unique quadruplets 
 [nums[a], nums[b], nums[c], nums[d]] such that:
 
 0 <= a, b, c, d < n
 a, b, c, and d are distinct.
 nums[a] + nums[b] + nums[c] + nums[d] == target
 You may return the answer in any order.
 
 Input: nums = [1,0,-1,0,-2,2], target = 0
 Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
 
 Input: nums = [2,2,2,2,2], target = 8
 Output: [[2,2,2,2]]
 
 Constraints:
 1 <= nums.length <= 200
 -109 <= nums[i] <= 109
 -109 <= target <= 109
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

vector<vector<int>> fourSum (vector<int>& nums, int target) {
    vector<vector<int>> solutions = {};
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums.size() && j != i; j++) {
            unordered_map<int, int> um;
            for (int k = 0; k < nums.size() && k != i && k != j; k++) {
                um[target - nums[i] - nums[j] - nums[k]] = k;
            }
            for (int k = 0; k < nums.size() && k != i && k != j; k++) {
                if (um.find(target - nums[i] - nums[j] - nums[k]) != um.end())
                    if (um[target - nums[i] - nums[j] - nums[k]] != k)
                        solutions.push_back({i, j, k, um[target - nums[i] - nums[j] - nums[k]]});
            }
        }
    }
    return solutions;
}

/* LC#15

Given an integer array nums, 
return all the triplets [nums[i], nums[j], nums[k]] 
such that i != j, i != k, and j != k, 
and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set 
must not contain duplicate triplets.

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]

Notice that the order of the output 
and the order of the triplets does not matter.
*/

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    unordered_map<int, vector<int>> members;
    set<vector<int>> entries;
    for (int i = 0; i < nums.size(); i++) {
        if (members.find(nums[i]) == members.end())
            members[nums[i]] = {i};
        else
            members[nums[i]].push_back(i);
    }
    for (int i = 0; i < nums.size() - 2; i++) {
        for (int j = i + 1; j < nums.size() - 1; j++) {
            int target = -(nums[i] + nums[j]);
            if (members.find(target) != members.end()) {
                for (auto &k : members[target]) {
                    if (k > i && k > j
                        && entries.find({nums[i], nums[j], nums[k]}) == entries.end()
                        && entries.find({nums[i], nums[k], nums[j]}) == entries.end()
                        && entries.find({nums[j], nums[i], nums[k]}) == entries.end()
                        && entries.find({nums[j], nums[k], nums[i]}) == entries.end()
                        && entries.find({nums[k], nums[i], nums[j]}) == entries.end()
                        && entries.find({nums[k], nums[j], nums[i]}) == entries.end()) {
                        result.push_back({nums[i], nums[j], nums[k]});
                        entries.insert({nums[i], nums[j], nums[k]});
                    }
                }
            }
        }
    }
    return result;
}

/* Approach:
1. sort the array
2. store the indices for evey element in a hashmap
3. for every pair elements, 
if the target - sum is in the map
with a greater index -- 
4. store in results
store the pair in a set.
*/

typedef pair<int, int> p;
// beats ~26% LC users
vector<vector<int>> threeSum2(vector<int>& nums) {
    vector<vector<int>> result;
    unordered_map<int, vector<int>> members;
    set<p> entries;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
        if (members.find(nums[i]) == members.end())
            members[nums[i]] = {i};
        else
            members[nums[i]].push_back(i);
    }
    /*for (auto &i : nums)
        cout << i << " ";
    cout << endl;
    for (auto &i : members) {
        cout << i.first << ": ";
        for (auto &j : i.second)
            cout << j << " ";
        cout << endl;
    }*/
    for (int i = 0; i < nums.size() - 2; i++) {
        for (int j = i + 1; j < nums.size() - 1; j++) {
            if (entries.find({nums[i], nums[j]}) == entries.end()) {
                int target = -(nums[i] + nums[j]);
                if (members.find(target) != members.end()) {
                    // cout << target << endl;
                    for (auto &k : members[target]) {
                        if (k > j && k > i) {
                            result.push_back({nums[i], nums[j], target});
                            entries.insert({nums[i], nums[j]});
                            entries.insert({nums[i], target});
                            entries.insert({nums[j], target});
                            break;
                        }
                    }
                }
            }
        }
    }
    return result;
}


/* LC#16

Given an integer array nums of length n 
and an integer target, 
find three integers in nums 
such that the sum is closest to target.

Return the sum of the three integers.

You may assume that each input 
would have exactly one solution.

repition and negative elements allowed in nums.
*/

int find_binary_search (vector<int>& nums, int i, int j, int t) {
    while (i < j) {
        if (nums[i + 1] == t)
            return i + 1;
        else if (nums[j - 1] == t)
            return j - 1;
        else if (nums[i + 1] > t)
            return -1;
        else if (nums[j - 1] < t)
            return -1;
        else if (j == i - 1) {
            if (abs(nums[i] - t) < abs(t - nums[j]))
                return i;
            else
                return j;
        }
        int mid = (i + j) / 2;
        if (nums[mid] == t)
            return mid;
        else if (nums[mid] > t) {
            if (abs(nums[mid] - t) < abs(t - nums[mid - 1]))
                return mid;
            else
                j = mid;
        }
        else if (nums[mid] < t) {
            if (abs(nums[mid] - t) < abs(t - nums[mid + 1]))
                return mid;
            else
                i = mid;
        }
    }
    return -1;
}

const int max_int = 1000000000;

int threeSumClosest(vector<int>& nums, int target) {
    int ans = max_int;
    sort(nums.begin(), nums.end()); // O(n log n)
    for (int i = 0; i < nums.size() - 2; i++) {
        for (int j = nums.size(); j > i + 1; j--) { // O(n ^ 2)
            int t = target - (nums[i] + nums[j]);
            int k = find_binary_search(nums, i, j, t); // for binary search, O(log n)
            if (abs(nums[i] + nums[j] + nums[k] - target) < abs(target - ans)) {
                ans = nums[i] + nums[j] + nums[k];
            }
        }
    }
    return ans;
}

// O(n^2)
// beats ~98% LC users
int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int ans = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < nums.size() - 2; i++) {
        int j = i + 1, k = nums.size() - 1;
        int t = target - nums[i];
        while (j < k) {
            if (abs(nums[i] + nums[j] + nums[k] - target) < abs(ans - target))
                ans = nums[i] + nums[j] + nums[k];
            if (nums[j] + nums[k] == t)
                return target;
            else if (nums[j] + nums[k] < t)
                j++;
            else if (nums[j] + nums[k] > t)
                k--;
        }
    }
    return ans;
}

/*
int threeSumClosest(vector<int>& nums, int target) {
    int ans = max_int;
    sort(nums.begin(), nums.end()); // O(n log n)
    unordered_map<int, vector<int>> elts;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == nums[i - 1]) 
            elts[nums[i]].push_back(i);
        else
            elts[nums[i]] = {i};
    }
    for (int i = 0; i < nums.size() - 2; i++) {
        for (int j = nums.size(); j > i + 1; j--) { // O(n ^ 2)
            int t = target - (nums[i] + nums[j]);
            int k = find_binary_search(nums, i, j, t); // for binary search, O(log n)
            if (abs(nums[i] + nums[j] + nums[k] - target) < abs(target - ans)) {
                ans = nums[i] + nums[j] + nums[k];
            }
        }
    }
    return ans;
}
*/

int main () {
    vector<int> nums = {1,0,-1,0,-2,2};
    int target = 0;
    vector<vector<int>> solutions = fourSum(nums, target);
    for (auto &i : solutions) {
        for (auto &j : i)
            cout << j << " ";
        cout << endl;
    }

    nums = {0, 0, 0}; // {-1,0,1,2,-1,-4};
    solutions = threeSum2(nums);
    for (auto &i : solutions) {
        for (auto &j : i)
            cout << j << " ";
        cout << endl;
    }
    return 0;
}
