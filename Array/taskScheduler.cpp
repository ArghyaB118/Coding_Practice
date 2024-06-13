/* LC#2365

You are given a 0-indexed array of positive integers tasks, 
representing tasks that need to be completed in order, 
where tasks[i] represents the type of the ith task.

You are also given a positive integer space, 
which represents the minimum number of days 
that must pass after the completion of a task 
before another task of the same type can be performed.

Each day, until all tasks have been completed, 
you must either:

Complete the next task from tasks, or
Take a break.
Return the minimum number of days needed to complete all tasks.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// beats ~70% LC users
long long taskSchedulerII(vector<int>& tasks, int space) {
	long long days = 1;
	unordered_map<int, long long> lastIndex;
	for (int i = 0; i < tasks.size(); i++) {
		if (lastIndex.find(tasks[i]) != lastIndex.end() && days - lastIndex[tasks[i]] <= space) {
			days = lastIndex[tasks[i]] + space + 1;
		}
		lastIndex[tasks[i]] = days;
		days++;
	}
	return lastIndex[tasks.back()];
}

int main () {
	vector<int> tasks = {1,2,1,2,3,1};
	int space = 3;
	cout << taskSchedulerII(tasks, space) << endl;
	return 0;
}