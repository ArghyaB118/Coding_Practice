/* LC#56
 
 Given an array of intervals where intervals[i] = [starti, endi], 
 merge all overlapping intervals, 
 and return an array of the non-overlapping intervals 
 that cover all the intervals in the input.
 
 Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 Output: [[1,6],[8,10],[15,18]]
 Explanation: Since intervals [1,3] and [2,6] overlap, 
 merge them into [1,6].
 
 Input: intervals = [[1,4],[4,5]]
 Output: [[1,5]]
 Explanation: Intervals [1,4] and [4,5] are considered overlapping.*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct comparator {
	bool operator() (const vector<int>& a, const vector<int>& b) {
		return a[0] < b[0];
	};
} cmp;

vector<vector<int>> merge (vector<vector<int>>& intervals) {
	sort(intervals.begin(), intervals.end(), cmp);
	stack<vector<int>> st; st.push(intervals[0]);
	for (int i = 0; i < intervals.size(); i++) {
		if (st.top()[1] < intervals[i][0])
			st.push(intervals[i]);
		else {
			vector<int> tmp = st.top(); st.pop();
			st.push({min(tmp[0], intervals[i][0]), max(tmp[1], intervals[i][1])});
		}
	}
	intervals.clear();
	while (!st.empty()) {
		intervals.push_back(st.top());
		st.pop();
	}
	sort(intervals.begin(), intervals.end(), cmp); // It may be skipped depending on the requirement on the output
	return intervals;
}

// Although this is more simplified as a code, 
// but using only vector is not a good idea in terms of performance.
// Cost = O(sort) + O(n) = O(n log n)
// beats ~48% LC users
vector<vector<int>> merge2 (vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> result;
    //for (auto i : intervals)
    //    cout << i[0] << " " << i[1] << endl;
    for (auto i : intervals) {
        if (result.empty())
            result.push_back(i);
        else {
            if (i[0] > result.back()[1])
                result.push_back(i);
            else {
                vector<int> tmp = {min(i[0], result.back()[0]), max(i[1], result.back()[1])};
                result.back() = tmp;
            }
        }
    }
    return result;
}

/* LC Facebook problem discussions

You are given two lists of closed intervals, 
firstList and secondList, where firstList[i] = [starti, endi] 
and secondList[j] = [startj, endj]. 
Each list of intervals is pairwise disjoint and in sorted order.

Return the union of these two interval lists.

A closed interval [a, b] (with a <= b) denotes 
the set of real numbers x with a <= x <= b.
*/

vector<vector<int>> mergeIntervalLists
	(vector<vector<int>>& firstList, 
		vector<vector<int>>& secondList) {
	stack<vector<int>> st;
	int i = 0, j = 0;
	while (i < firstList.size() && j < secondList.size()) {
		if (st.empty() && firstList[i][0] <= secondList[j][0]) {
			st.push(firstList[i]); i++;
		}
		else if (st.empty() && firstList[i][0] > secondList[j][0]) {
			st.push(secondList[i]); j++;
		}
		else if (firstList[i][0] > st.top()[1] && secondList[j][0] > st.top()[1]) {
			if (firstList[i][0] <= secondList[j][0]) {
				st.push(firstList[i]); i++;
			}
			else if (firstList[i][0] > secondList[j][0]) {
				st.push(secondList[i]); j++;
			}
		}
		else if (firstList[i][0] <= st.top()[1] && secondList[j][0] > st.top()[1]) {
			vector<int> tmp = st.top(); st.pop();
			tmp[0] = min(tmp[0], firstList[i][0]);
			tmp[1] = max(tmp[1], firstList[i][1]);
			st.push(tmp);
			i++;
		}
		else if (firstList[i][0] > st.top()[1] && secondList[j][0] <= st.top()[1]) {
			vector<int> tmp = st.top(); st.pop();
			tmp[0] = min(tmp[0], secondList[j][0]);
			tmp[1] = max(tmp[1], secondList[j][1]);
			st.push(tmp);
			j++;
		}
	}
	vector<vector<int>> result;
	while (!st.empty()) {
		result.push_back(st.top());
		st.pop();
	}
	reverse(result.begin(), result.end());
	return result;
}

/* LC#435

Given an array of intervals intervals 
where intervals[i] = [starti, endi], 
return the minimum number of intervals 
you need to remove to make the rest 
of the intervals non-overlapping.
*/

// beats ~70% LC users
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
	if (intervals.empty())
		return 0;
	else if (intervals.size() == 1)
		return 0;
	sort(intervals.begin(), intervals.end());
	stack<vector<int>> st;
	st.push(intervals[0]);
	int j = 1, count = 0;
	while (!st.empty() && j < intervals.size()) {
		if (st.top()[1] <= intervals[j][0]) {
			st.push(intervals[j]);
			j++;
		}
		else if (st.top()[1] > intervals[j][1]) {
			st.pop();
			count++;
			st.push(intervals[j]);
			j++;
		}
		else if (st.top()[1] <= intervals[j][1]) {
			count++;
			j++;
		}
	}
	return count;
}

int main () {
	vector<vector<int>> intervals{{2,6},{1,3},{8,10},{9,15}};
	merge(intervals);
	for (auto & x : intervals) {
		for (auto & y : x)
			cout << y << " ";
		cout << endl;
	}
    
    intervals = {{2,6},{1,3},{8,10},{9,15}};
    vector<vector<int>> result = merge2(intervals);
    for (auto i : result)
        cout << i[0] << " " << i[1] << endl;

    cout << "merging list of intervals" << endl;
	vector<vector<int>> intervals1{{0,2},{5,10},{13,23},{24,25}};
    vector<vector<int>> intervals2{{1,5},{8,12},{15,24},{25,26}};
    
    vector<vector<int>> result2 = mergeIntervalLists (intervals1, intervals2);
    for (auto i : result2)
        cout << i[0] << " " << i[1] << endl;
	return 0;
}
