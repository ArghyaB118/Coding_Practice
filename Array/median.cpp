/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, 
return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).
*/

#include <iostream>
#include <vector>
using namespace std;


// Traverse through both the arrays
// Stopping criterion: when find the median/ one of the arrays end
// Cost: O(m + n)
int findMedian(vector<int>& nums1, vector<int>& nums2) {
	int m = nums1.size(), n = nums2.size(), count = 0, count1 = 0, count2 = 0, median = -1;
	if ((m + n) % 2 == 1) {
		while (count < (m + n) / 2) {
			if (count1 < m && count2 < n) {
				if (nums1[count1] < nums2[count2]) {
					count1++; count++;
					median = nums1[count1];
				}
				else {
					median = nums2[count2];
					count2++; count++;
				}
			}
			else if (count1 == m) {
				median = nums2[count2 + (m + n) / 2 - count];
			}
			else if (count2 == n) {
				median = nums1[count1 + (m + n) / 2 - count];
			}
		}
	} 
	return median;
}

/*
Can we do better?
O(log (m + n)) -- 
Idea: Do binary search. 
If one of the arrays have size 0, 
	return median of the other array
If both the medians are the same, 
	return that as the overall median
If size(smaller array) = 1: 
		If size(larger array) = 1, return average 
		Else if size(larger array) = even, return median after merge 
Else
	Recursively find out the half that do not contribute to the answer
*/

struct vec {
	vector<int> v;
	int left, right;
};

int median(struct vec v1) {
	return (((v1.right - v1.left) / 2) % 2 == 0) ? v1.v[(v1.left + v1.right) / 2] : (v1.v[(v1.left + v1.right) / 2 - 1] + v1.v[(v1.left + v1.right) / 2]) / 2;
}

int findMedian2(struct vec v1, struct vec v2) {
	if (median(v1) == median(v2))
		return median(v1);
	else if (median(v1) <= median(v2)) {
		v1.left = v1.left + (v1.right - v1.left) / 2;
		return findMedian2(v1, v2);
	}
	return 0;
}



double findMedianSortedArrays (vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() + nums2.size() % 2 != 0)
        findMedianRecur (nums1, 0, nums1.size() - 1, nums2, 0, nums2.size() - 1);
}


/* LC#295

The median is the middle value 
in an ordered integer list. 
If the size of the list is even, 
there is no middle value, 
and the median is the mean 
of the two middle values.
*/

class MedianFinder {
    vector<int> v;
public:
    MedianFinder() {
        this->v = {};
    }
    
    void addNum(int num) {
        this->v.push_back(num);
    }
    
    double findMedian() {
        sort(this->v.begin(), this->v.end());
        int n = this->v.size();
        if (n % 2 != 0)
            return this->v[n / 2];
        else
            return ((double)this->v[n / 2 - 1] + (double)this->v[n / 2]) / 2;
    }
};

class MedianFinder {
    map<int, int> counts;
    int count;
public:
    MedianFinder() {
    	this->count = 0;
    	counts.clear();
    }
    
    void addNum(int num) {
        this->counts[num]++;
        count++;
    }
    
    double findMedian() {
        if (this->count == 0)
            return -1;
        else if (this->count == 1)
            return counts.begin()->first;
        else if (this->count == 2) {
            double ans = (counts.begin()->first+ counts.rbegin()->first);
            cout << counts.begin()->first << counts.end()->first << endl;
            return ans / 2;
        }

    	int cumulative_count = 0;
    	if (this->count % 2 != 0) {
    		for (auto& i : this->counts) {
    			cumulative_count += i.second;
    			if (cumulative_count > this->count / 2)
    				return i.first;
    		}
    	}
    	else {
    		double tmp = 0;
    		for (auto& i : this->counts) {
    			cumulative_count += i.second;
    			if (cumulative_count >= this->count / 2 + 1) {
                    if (tmp == 0)
                        return i.first;
                    else {
                        tmp += i.first;
                        return tmp / 2;
                    }
                }
    			else if (cumulative_count == this->count / 2)
    				tmp = i.first;
            }
    	}
        return -1;
    }
};

class MedianFinder {
    priority_queue<int> minHeap;
    priority_queue<int, vector<int>, gerater<int>> maxHeap;
public:
    MedianFinder() {
        minHeap.clear(); maxHeap.clear();
    }
    
    void addNum(int num) {
    	if (maxHeap.size() >= minHeap.size() && maxHeap.top() <= num)
    		minHeap.push(num);
    	else if (maxHeap.size() >= minHeap.size() && maxHeap.top() > num) {
    		int tmp = maxHeap.top();
    		maxHeap.push(num);
    		minHeap.push(tmp);
    	}
    	else if (maxHeap.size() < minHeap.size() && maxHeap.top() >= num)
    		maxHeap.push(num);
    	else if (maxHeap.size() < minHeap.size() && minHeap.top() < num) {
    		int tmp = maxHeap.top();
    		maxHeap.push(num);
    		minHeap.push(tmp);
    	}
    }
    
    double findMedian() {
        sort(this->v.begin(), this->v.end());
        int n = this->v.size();
        if (n % 2 != 0)
            return this->v[n / 2];
        else
            return ((double)this->v[n / 2 - 1] + (double)this->v[n / 2]) / 2;
    }
};

int main() {
	vector<int> nums1{1,2,3,4,5};
	vector<int> nums2{2,3,5,7};
	cout << "The median is: " << findMedian(nums1, nums2) << endl;
	struct vec v1 = {nums1, 0, 4}, v2 = {nums2, 0, 3};
	cout << findMedian2(v1, v2) << endl;
	return 0;
}
