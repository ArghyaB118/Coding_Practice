/* LC#1331

Given an array of integers arr, 
replace each element with its rank.

The rank represents how large the element is. 
The rank has the following rules:

Rank is an integer starting from 1.
The larger the element, the larger the rank. 
If two elements are equal, 
their rank must be the same.
Rank should be as small as possible.
*/

// beats ~56% LC users
vector<int> arrayRankTransform(vector<int>& arr) {
	set<int> s(arr.begin(), arr.end());
	int rank = 1;
	unordered_map<int, int> ranks;
	for (auto &i : s) {
		ranks[i] = rank;
		rank++;
	}
	for (auto &i : arr)
		i = ranks[i];
	return arr;
}