/* LC#986

You are given two lists of closed intervals, 
firstList and secondList, 
where firstList[i] = [starti, endi] 
and secondList[j] = [startj, endj]. 
Each list of intervals is 
pairwise disjoint and in sorted order.

Return the intersection of these two interval lists.

A closed interval [a, b] (with a <= b) denotes 
the set of real numbers x with a <= x <= b.

The intersection of two closed intervals is 
a set of real numbers that are either empty or 
represented as a closed interval. 
For example, 
the intersection of [1, 3] and [2, 4] is [2, 3].

Input: 
firstList = [[0,2],[5,10],[13,23],[24,25]], 
secondList = [[1,5],[8,12],[15,24],[25,26]]
Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
using namespace std;

int get_span (vector<vector<int>>& List) {
	int span = 0;
	for (auto &i : List)
		span += (i[1] - i[0]);
	return span;
}

// this approach treats [15, 24]
// and [15, 23] and [24, 24] as the same.
vector<vector<int>> intervalIntersection
	(vector<vector<int>>& firstList, 
		vector<vector<int>>& secondList) {
	vector<vector<int>> result;
	//int spanFirstList = get_span(firstList);
	//int spanSecondList = get_span(secondList);
	//if (spanFirstList < spanSecondList) {
		unordered_set<int> items;
		for (auto &i : firstList) {
			for (int j = i[0]; j <= i[1]; j++)
				items.insert(j);
		}
		for (auto &i : secondList) {
			int j = i[0], start = 0;
			bool continuing = false;
			while (j <= i[1]) {
				if (items.find(j) == items.end() && !continuing)
					j++;
				else if (items.find(j) == items.end() && continuing) {
					result.push_back({start, j - 1}); 
					continuing = false; j++;
				}
				else if (items.find(j) != items.end() && continuing) {
					j++;
				}
				else if (items.find(j) != items.end() && !continuing) {
					start = j; continuing = true; j++;
				}
			}
			if (continuing) {
				result.push_back({start, i[1]});
			}
		}
	//}
	return result;
}

// beats ~47% LC users
vector<vector<int>> intervalIntersection2
(vector<vector<int>>& firstList, 
	vector<vector<int>>& secondList) {
	vector<vector<int>> result;
	if (firstList.size() == 0 || secondList.size() == 0)
		return result;
	int i = 0, j = 0;
	while (i < firstList.size() && j < secondList.size()) {
		if (firstList[i][1] < secondList[j][0])
			i++;
		else if (secondList[j][1] < firstList[i][0])
			j++;

		else {
			result.push_back({max(firstList[i][0], secondList[j][0]), 
				min(firstList[i][1], secondList[j][1])});
			if (firstList[i][1] < secondList[j][1])
				i++;
			else
				j++;
		}
	}
	return result;
}


/* LC#57

You are given an array of non-overlapping intervals 
where intervals[i] = [starti, endi] 
represent the start and the end 
of the ith interval and intervals is sorted 
in ascending order by starti. 
You are also given an interval 
newInterval = [start, end] 
that represents the start and end of another interval.

Insert newInterval into intervals 
such that intervals is still sorted in ascending order 
by starti and intervals still 
does not have any overlapping intervals 
(merge overlapping intervals if necessary).

Return intervals after the insertion.
*/

vector<vector<int>> insertIntervals
(vector<vector<int>>& intervals, vector<int>& newInterval) {
	if (intervals.size() == 0) {
		intervals.push_back(newInterval);
		return intervals;
	}
	else if (intervals.back()[1] < newInterval[0]) {
        intervals.push_back(newInterval);
        return intervals;
    }
    else if (intervals[0][0] > newInterval[1]) {
        intervals.insert(intervals.begin(), newInterval);
        return intervals;
    }
	int i = 0;
	while (i < intervals.size()) {
		if (intervals[i][1] >= newInterval[0]) {
			vector<int> tmp = intervals[i];
			tmp[0] = min(tmp[0], newInterval[0]);
			tmp[1] = max(tmp[1], newInterval[1]);
			intervals[i] = tmp;
			break;
		}
		else
			i++;
	}
	if (i == intervals.size() - 1)
		return intervals;
	int j = i + 1, count = 0;
	while (intervals[j][0] <= intervals[i][1]) {
		intervals[i][1] = max(intervals[i][1], intervals[j][1]);
		j++; count++;
	}
	if (count == 0)
		return intervals;
	intervals.erase(intervals.begin() + i + 1, intervals.begin() + i + 1 + count);
	return intervals;
}

vector<vector<int>> insertIntervalsBinarySearch
(vector<vector<int>>& intervals, vector<int>& newInterval) {
	if (intervals.size() == 0) {
		intervals.push_back(newInterval);
		return intervals;
	}
	else if (intervals.back()[1] < newInterval[0]) {
        intervals.push_back(newInterval);
        return intervals;
    }
    else if (intervals[0][0] > newInterval[1]) {
        intervals.insert(intervals.begin(), newInterval);
        return intervals;
    }
	int i = 0;
	while (i < intervals.size()) {
		if (intervals[i][1] >= newInterval[0]) {
			vector<int> tmp = intervals[i];
			tmp[0] = min(tmp[0], newInterval[0]);
			tmp[1] = max(tmp[1], newInterval[1]);
			intervals[i] = tmp;
			break;
		}
		else
			i++;
	}
	if (i == intervals.size() - 1)
		return intervals;
	int j = i + 1, count = 0;
	while (intervals[j][0] <= intervals[i][1]) {
		intervals[i][1] = max(intervals[i][1], intervals[j][1]);
		j++; count++;
	}
	if (count == 0)
		return intervals;
	intervals.erase(intervals.begin() + i + 1, intervals.begin() + i + 1 + count);
	return intervals;
}


/* LC#349

Given two integer arrays nums1 and nums2, 
return an array of their intersection. 
Each element in the result must be unique 
and you may return the result in any order.
*/

// beats ~50% LC users
vector<int> intersection1(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> s1;
    for (int &i : nums1)
        s1.insert(i);
    unordered_set<int> s2;
    for (int &i : nums2) {
        if (s1.find(i) != s1.end())
            s2.insert(i);
    }
    vector<int> res = {};
    for (auto &i : s2)
        res.push_back(i);
    return res;
}

// beats ~25% LC users
vector<int> intersection2(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> s1, s2;
    for (int &i : nums1)
        s1.insert(i);
    for (int &i : nums2)
        s2.insert(i);

	vector<int> res = {};
    if (s1.size() <= s2.size()) {
    	for (auto &i : s1)
    		if (s2.find(i) != s2.end())
    			res.push_back(i);
    }
    else {
    	for (auto &i : s2)
    		if (s1.find(i) != s1.end())
    			res.push_back(i);
    }
    return res;
}

int main () {
	vector<vector<int>> intervals1{{0,2},{5,10},{13,23},{24,25}};
    vector<vector<int>> intervals2{{1,5},{8,12},{15,24},{25,26}};
    
    vector<vector<int>> result = intervalIntersection2 (intervals1, intervals2);
    for (auto i : result)
        cout << i[0] << " " << i[1] << endl;

	return 0;
}