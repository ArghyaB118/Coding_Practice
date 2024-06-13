/* LC#1891

Cutting Ribbons

You are given an integer array ribbons, 
where ribbons[i] represents the length of the ith ribbon, and an integer k. 
You may cut any of the ribbons into any number of segments of positive integer lengths, 
or perform no cuts at all.

For example, if you have a ribbon of length 4, you can:
Keep the ribbon of length 4,
Cut it into one ribbon of length 3 and one ribbon of length 1,
Cut it into two ribbons of length 2,
Cut it into one ribbon of length 2 and two ribbons of length 1, or
Cut it into four ribbons of length 1.
Your goal is to obtain k ribbons of all the same positive integer length. 
You are allowed to throw away any excess ribbon as a result of cutting.

Return the maximum possible positive integer length that you can obtain k ribbons of, 
or 0 if you cannot obtain k ribbons of the same length.

Input: ribbons = [9,7,5], k = 3
Output: 5

Input: ribbons = [7,5,9], k = 4
Output: 4

Input: ribbons = [5,7,9], k = 22
Output: 0
*/

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

bool possibleCut (vector<int>& ribbons, int k, int length) {
	int count = 0;
	for (int i = 0; i < ribbons.size(); i++)
		count += ribbons[i] / length;
	return (count < k) ? false : true;
}

// beats ~75% LC users
int maxLengthRibbon(vector<int>& ribbons, int k) {
	unsigned long long total_length = 0;
    for (auto &i : ribbons)
        total_length += i;
	int max = total_length / k, min = 1, result;
	// signed interger overflow
	// int max = accumulate(ribbons.begin(), ribbons.end(), 0) / k, min = 1, result;
	if (max <= min)
		return max;
	while(min <= max) {
		int mid = (min + max) / 2;
		if (possibleCut(ribbons, k, mid)) {
			min = mid + 1;
			result = mid;
		}
		else
			max = mid - 1;
	}
	return result;
}

int main () {
	vector<int> ribbons = {9,7,5};
	cout << maxLengthRibbon(ribbons, 3) << endl;
	return 0;
}