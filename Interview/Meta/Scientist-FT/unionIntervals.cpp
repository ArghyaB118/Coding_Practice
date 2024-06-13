// QUESTION

// Consider the concept of a 'sorted, non-overlapping interval list' 
// - which is an array of intervals that don't overlap with each other and are sorted by interval start.
// Given two of these interval lists, return a 3rd interval list that is the union of the input interval lists.

// For example:

// // Input:
// [[1,2], [3,9]]
// [[4,6], [8,10], [11,12]]

// // Output should be:
// [[1,2], [3,10], [11,12]]

// lengths are m, n respectively =. O(m + n) space O(max(m, n)) time

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef pair<int, int> interval;

vector<interval> unionIntervals (vector<interval>& intervals1, vector<interval>& intervals2) {
  if (intervals1.size() == 0)
    return intervals2;
  if (intervals2.size() == 0)
    return intervals1;
  stack<interval> st;
  int i = 0, j= 0;
  if (intervals1[i].first <= intervals2[j].first) {
    st.push(intervals1[i]); i++;
  }
  else {
    st.push(intervals2[j]); j++;
  }
  while (i < intervals1.size() && j < intervals2.size()) {
    if (intervals1[i].first <= intervals2[j].first) {
      if (intervals1[i].first > st.top().second) {
        st.push(intervals1[i]); 
        i++;
      }
      else {
        interval tmp = st.top(); st.pop();
        tmp.first = min(intervals1[i].first, tmp.first);
        tmp.second = max(intervals1[i].second, tmp.second);
        st.push(tmp);
        i++;
      }
    }
    else {
      if (intervals2[j].first > st.top().second) {
        st.push(intervals2[j]); 
        j++;
      }
      else {
        interval tmp = st.top(); st.pop();
        tmp.first = min(intervals2[j].first, tmp.first);
        tmp.second = max(intervals2[j].second, tmp.second);
        st.push(tmp);
        j++;
      }
    }
  }
  if (i < intervals1.size()) {
    while (intervals1[i].first < st.top().second) {
      interval tmp = st.top(); st.pop();
      tmp.first = min(intervals1[i].first, tmp.first);
      tmp.second = max(intervals1[i].second, tmp.second);
      st.push(tmp);
      i++;
    }
  }
  else if (j < intervals2.size()) {
    while (intervals2[j].first < st.top().second) {
      interval tmp = st.top(); st.pop();
      tmp.first = min(intervals2[j].first, tmp.first);
      tmp.second = max(intervals2[j].second, tmp.second);
      st.push(tmp);
      j++;
    }
  }
  
  vector<interval> result;
  while (!st.empty()) {
    result.push_back(st.top());
    st.pop();
  }
  reverse(result.begin(), result.end());

  while (i < intervals1.size()) {
    result.push_back(intervals1[i]);
    i++;
  }
  while (j < intervals2.size()) {
    result.push_back(intervals2[j]);
    j++;
  }

  return result;
}

int main() {
  vector<interval> intervals1 = {{1,2}, {3,9}};
  vector<interval> intervals2 = {{4,6}, {8,10}, {11,12}};
  vector<interval> union_intervals = unionIntervals (intervals1, intervals2);
  for (auto &i : union_intervals)
    cout << i.first << " " << i.second << endl;
  return 0;
}






