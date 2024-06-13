/*

Flipping matrix

Flip any row and any column of a matrix
as ,any times as possible.

Dimension: 2n * 2n
Objective: maximize the sum of the top-left
quadrant of size n * n
*/

// Key observation:
// For each cell, you can maximize the cell's value
// by taking the maximum of 4 possible elements.
// https://www.geeksforgeeks.org/maximize-sum-n-x-n-upper-left-sub-matrix-given-2n-x-2n-matrix/

int flippingMatrix(vector<vector<int>> matrix) {
    int n = matrix.size() / 2;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<int> v = {matrix[i][j], matrix[2 * n - i - 1][2 * n - j -1], matrix[2 * n - i - 1][j], matrix[i][2 * n - j - 1]};
            sort(v.begin(), v.end());
            // matrix[i][j] = v[3];
			sum += v[3]; 
		}
	}
	return sum; 
}