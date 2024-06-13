/* LC#128

Given an unsorted array of integers nums, 
return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence 
is [1, 2, 3, 4]. Therefore its length is 4.

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9

Constraints:

0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

//typedef pair<int, int> pp;
int longestConsecutive (vector<int>& nums) {
    unordered_set<int> s;
    for (int & i : nums)
        s.insert(i);
    int tmp = 0, count = 0;
    cout << s.size() << endl;
    while (!s.empty()) {
        auto it = s.begin();
        tmp = 1;
        int i = 1;
        while (s.find(*it + i) != s.end()) {
            tmp++; 
            s.erase(*it + i); 
            i++;
        }
        i = 1;
        while (s.find(*it - i) != s.end()) {
            tmp++; 
            s.erase(*it - i); 
            i++;
        }
        s.erase(it);
        count = max(count, tmp); cout << count << endl;
        tmp = 0;
    }
    return max(count, tmp);
}

// Bad: has to go through the entire range
int longestConsecutive2 (vector<int>& nums) {
    unordered_set<int> s;
    int minm = 1000000000, maxm = -1000000000;
    for (int & i : nums) {
        if (i > maxm)
            maxm = i;
        if (i < minm)
            minm = i;
        s.insert(i);
    }
    int length = 0, tmp = 0;
    for (int i = minm; i <= maxm; i++) {
        if (s.find(i) != s.end())
            tmp++;
        else {
            length = std::max(tmp, length);
            tmp = 0;
        }
    }
    length = max(length, tmp);
    return length;
}

#include <unordered_map>
using namespace std;
#define MAX 1000
#define MIN 0

/* Why the hashmap?
 Because if the array is {1, 1, 2, 3, 3}, the program will return false.
 The program cannot handle repitition without the hashmap.
 
 Why not a boolean array visited?
 We can, but then the min and max has to be calculated first, then mark the ones we visit.*/
bool areConsecutive (int arr[], int n) {
    int minElt = MAX, maxElt = MIN;
    unordered_map<int, int> hashmap;
    for (int i = 0; i < n; i++) {
        minElt = std::min(minElt, arr[i]);
        maxElt = std::max(maxElt, arr[i]);
        hashmap[arr[i]] = 1;
    }
    // works only without repitition
    // needs to be removed in case repitition is allowed
    // otherwise fails in the case {1, 3, 2, 3}
    /* if (maxElt - minElt + 1 == n)
        return true; */
    if (maxElt - minElt + 1 > n)
        return false;
    for (int i = minElt; i <= maxElt; i++)
        if (hashmap.find(i) == hashmap.end())
            return false;
    return true;
}


/* LC#34

Given an array of integers nums sorted 
in non-decreasing order, 
find the starting and ending position 
of a given target value.

If target is not found in the array, 
return [-1, -1].

You must write an algorithm with O(log n) 
runtime complexity.
*/

int binary_search_first_elt (vector<int>& nums, int target) {
    if (nums.size() == 0)
        return -1;
    else if (nums.size() == 1 && nums[0] == target)
        return 0;
    else if (nums.size() == 1 && nums[0] != target)
        return -1;
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        if (right - left == 1 && nums[left] < target && nums[right] == target)
            return right;
        else if (right - left == 1 && nums[left] < target && nums[right] > target)
            return -1;
        int mid = (left + right) / 2;
        if (nums[mid] < target)
            left = mid;
        else if (nums[mid] >= target)
            right = mid;
    }
    return -1;
}

int binary_search_last_elt (vector<int>& nums, int target) {
    if (nums.size() == 0)
        return -1;
    else if (nums.size() == 1 && nums[0] == target)
        return 0;
    else if (nums.size() == 1 && nums[0] != target)
        return -1;
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        if (right - left == 1 && nums[left] == target && nums[right] > target)
            return left;
        else if (right - left == 1 && nums[left] < target && nums[right] > target)
            return -1;
        int mid = (left + right) / 2;
        if (nums[mid] <= target)
            left = mid;
        else if (nums[mid] > target)
            right = mid;
    }
    return -1;
}

vector<int> searchRange(vector<int>& nums, int target) {
    return {binary_search_first_elt(nums, target), 
    binary_search_last_elt(nums, target)};
}

int main () {
    int arr[]= {5, 4, 2, 5, 3, 1, 6, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << (boolalpha) << areConsecutive(arr, n) << endl;
    vector<int> v = {0,3,7,2,5,8,4,6,0,1};
    cout << longestConsecutive(v) << endl;
    return 0;
}
