/* LC#715
 
 A Range Module is a module that tracks ranges of numbers. Design a data structure to track the ranges represented as half-open intervals and query about them.
 
 A half-open interval [left, right) denotes all the real numbers x where left <= x < right.

 Implement the RangeModule class:

 RangeModule() Initializes the object of the data structure.
 void addRange(int left, int right) Adds the half-open interval [left, right), tracking every real number in that interval. Adding an interval that partially overlaps with currently tracked numbers should add any numbers in the interval [left, right) that are not already tracked.
 boolean queryRange(int left, int right) Returns true if every real number in the interval [left, right) is currently being tracked, and false otherwise.
 void removeRange(int left, int right) Stops tracking every real number currently being tracked in the half-open interval [left, right).*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;


/*typedef pair<int, int> range;

class RangeModule {
public:
    vector<range> ranges = {};
    
    RangeModule() {
        
    }
    
    void addRange (int left, int right) {
        if (this->ranges.empty())
            this->ranges.push_back({left, right});
        else {
            int idx = 0;
            while (idx < this->ranges.size()) {
                if (this->ranges[idx].second < left) {
                    this->ranges.insert(this->ranges.begin() + idx + 1, {left, right});
                    break;
                }
                else if (this->ranges[idx].first > right) {
                    this->ranges.insert(this->ranges.begin() + idx, {left, right});
                    break;
                }
                else if (this->ranges[idx].first < left && this->ranges[idx].second > right)
                    break;
                else
                    idx++;
            }
        }
        cout << "Size: " << this->ranges.size() << endl;
        for (auto it = this->ranges.begin(); it != this->ranges.end(); it++)
            cout << it->first << " " << it->second << endl;
    }
    
    bool queryRange(int left, int right) {
        return true;
    }
    
    void removeRange(int left, int right) {
        
    }
};
*/

class RangeModule {
public:
    unordered_set<int> range;
    
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        for (int i = left; i < right; i++)
            if (range.find(i) == range.end())
                range.insert(i);
    }
    
    bool queryRange(int left, int right) {
        for (int i = left; i < right; i++)
            if (range.find(i) == range.end())
                return false;
        return true;
    }
    
    void removeRange(int left, int right) {
        for (int i = left; i < right; i++)
            if (range.find(i) != range.end())
                range.erase(i);
    }
};

/* LC#303

Given an integer array nums, 
handle multiple queries of the following type:

Calculate the sum of the elements of nums 
between indices left and right inclusive 
where left <= right.
Implement the NumArray class:

NumArray(int[] nums) 
Initializes the object with the integer array nums.

int sumRange(int left, int right) 
Returns the sum of the elements of nums 
between indices left and right inclusive 
(i.e. nums[left] + nums[left + 1] + ... + nums[right]).
*/

// beats ~61% LC users
class NumArray {
    vector<int> nums;
public:
    NumArray(vector<int>& nums) {
        this->nums.push_back(nums[0]);
        if (nums.size() > 1) {
            for (int j = 1; j < nums.size(); j++) {
                nums[j] += nums[j - 1];
                this->nums.push_back(nums[j]);
            }
        }
    }
    
    int sumRange(int left, int right) {
        if (left == 0)
            return this->nums[right];
        return this->nums[right] - this->nums[left - 1];
    }
};

int main () {
    RangeModule *obj = new RangeModule();
    obj->addRange(5, 10); obj->addRange(11, 15); obj->addRange(1, 4); obj->addRange(2, 3);
    obj->removeRange(1, 10);
    return 0;
}
