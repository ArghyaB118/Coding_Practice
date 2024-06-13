/* LC#498

Given an m x n matrix mat, 
return an array of all the elements of the array 
in a diagonal order.

Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,4,7,5,3,6,8,9]

Constraints:
m == mat.length
n == mat[i].length
1 <= m, n <= 10^4
1 <= m * n <= 10^4
-10^5 <= mat[i][j] <= 10^5
*/

#include <iostream>
#include <vector>
using namespace std;

// beats ~70% LC users
vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
	int m = mat.size();
	int n = mat[0].size();
	vector<int> traversal;
	if (m == 1)
		return mat[0];
	bool reverse = false;
	vector<int> tmp = {};
	for (int i = 0; i < m; i++) {
		int k = i, j = 0; tmp.clear();
		while (k >= 0 && j < n) {
			tmp.push_back(mat[k][j]);
			k--; j++;
		}
		if (!reverse)
			traversal.insert(traversal.end(), tmp.begin(), tmp.end());
		else
			traversal.insert(traversal.end(), tmp.rbegin(), tmp.rend());
		reverse = !reverse;
	}
	if (n == 1)
		return traversal;
	for (int j = 1; j < n; j++) {
		int i = m - 1, k = j; tmp.clear();
		while (i >= 0 && k < n) {
			tmp.push_back(mat[i][k]);
			i--; k++;
		}
		if (!reverse) {
			traversal.insert(traversal.end(), tmp.begin(), tmp.end());
			tmp.clear();
		}
		else {
			traversal.insert(traversal.end(), tmp.rbegin(), tmp.rend());
			tmp.clear();
		}
		reverse = !reverse;
	}
	return traversal;
}

/* LC#766

Given an m x n matrix, 
return true if the matrix is Toeplitz. 
Otherwise, return false.

A matrix is Toeplitz 
if every diagonal from top-left 
to bottom-right has the same elements.

Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
Output: true
*/

// beats ~92% LC users
bool isToeplitzMatrix(vector<vector<int>>& matrix) {
	int m = matrix.size();
	int n = matrix[0].size();
	for (int j = 0; j < n; j++) {
		int i = 0, k = j;
		int tmp = matrix[i][k];
		while (i < m && k < n) {
			if (matrix[i][k] != tmp)
				return false;
			k++; i++;
		}
	}
	for (int i = 0; i < m; i++) {
		int k = i, j = 0;
		int tmp = matrix[k][j];
		while (k < m && j < n) {
			if (matrix[k][j] != tmp)
				return false;
			k++; j++;
		}
	}
	return true;
}

/* LC#1424

Given a 2D integer array nums, 
return all elements of nums 
in diagonal.
*/

// TLE!
vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
	int n = nums.size();
	int size = 0;
	vector<int> result;
	for (int i = 0; i < n; i++) {
		size += nums[i].size();
		int row = i, col = 0;
		while (row >= 0) {
			if (nums[row].size() > col)
				result.push_back(nums[row][col]);
			row--; col++;
		}
	}
	int j = 1;
	while (result.size() < size) {
		int row = n - 1, col = j;
		j++;
		while (row >= 0) {
			if (nums[row].size() > col)
				result.push_back(nums[row][col]);
			row--; col++;
		}
	}
	return result;
}

// slight improvement
// still TLE
vector<int> findDiagonalOrder2(vector<vector<int>>& nums) {
	int n = nums.size();
	int size = 0;
	vector<int> result;
    vector<int> colsize(n, 0);
	for (int i = 0; i < n; i++) {
        int s = nums[i].size();
		size += s;
        colsize[i] = s;
		int row = i, col = 0;
		while (row >= 0) {
			if (colsize[row] > col)
				result.push_back(nums[row][col]);
			row--; col++;
		}
	}
	int j = 1;
	while (result.size() < size) {
		int row = n - 1, col = j;
		j++;
		while (row >= 0) {
			if (colsize[row] > col)
				result.push_back(nums[row][col]);
			row--; col++;
		}
	}
	return result;
}

int main () {
	vector<vector<int>> mat = {{1,2,3}, {4,5,6}, {7,8,9}};
	vector<int> v = findDiagonalOrder(mat);
	for (auto &i : v)
		cout << i << " ";
	cout << endl;
	return 0;
}