/* LC#40

Given a collection of candidate numbers (candidates) 
and a target number (target), 
find all unique combinations in candidates 
where the candidate numbers sum to target.

Each number in candidates may only be used 
once in the combination.

Note: The solution set must not contain duplicate combinations.
Constraints:
1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30
*/

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
	vector<vector<int>> result;
	sort(candidates.begin(), candidates.end());
	queue<vector<int>> q;
	int n = candidates.size();
	for (int i = 0; i < n; i++) {
		if (candidates[i] == target)
			result.push_back({i});
		else if (candidates[i] < target)
			q.push({i});
	}
	while (!q.empty()) {
		vector<int> tmp = q.front();
		q.pop();
		if (tmp.back() < n - 1) {
			for (int j = tmp.back() + 1; j < n; j++) {
				
			}
		}
		
	}
}