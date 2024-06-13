/* LC#1091

Given an n x n binary matrix grid, 
return the length of the shortest clear path in the matrix. 
If there is no clear path, return -1.

A clear path in a binary matrix is a path 
from the top-left cell (i.e., (0, 0)) 
to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected 
(i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.
*/


typedef pair<int, int> cell;

void move8way (vector<vector<int>>& grid, queue<cell>& q, cell c, int n) {
	if (c.first - 1 >= 0 && c.second - 1 >= 0 && grid[c.first - 1][c.second - 1] == 0) {
		grid[c.first - 1][c.second - 1] = grid[c.first][c.second] + 1;
		q.push({c.first - 1, c.second - 1});
	}
	if (c.first - 1 >= 0 && grid[c.first - 1][c.second] == 0) {
		grid[c.first - 1][c.second] = grid[c.first][c.second] + 1;
		q.push({c.first - 1, c.second});
	}
	if (c.first - 1 >= 0 && c.second + 1 < n && grid[c.first - 1][c.second + 1] == 0) {
		grid[c.first - 1][c.second + 1] = grid[c.first][c.second] + 1;
		q.push({c.first - 1, c.second + 1});
	}
	if (c.second - 1 >= 0 && grid[c.first][c.second - 1] == 0) {
		grid[c.first][c.second - 1] = grid[c.first][c.second] + 1;
		q.push({c.first, c.second - 1});
	}
	if (c.second + 1 < n && grid[c.first][c.second + 1] == 0) {
		grid[c.first][c.second + 1] = grid[c.first][c.second] + 1;
		q.push({c.first, c.second + 1});
	}
	if (c.first + 1 < n && c.second - 1 >= 0 && grid[c.first + 1][c.second - 1] == 0) {
		grid[c.first + 1][c.second - 1] = grid[c.first][c.second] + 1;
		q.push({c.first + 1, c.second - 1});
	}
	if (c.first + 1 < n && grid[c.first + 1][c.second] == 0) {
		grid[c.first + 1][c.second] = grid[c.first][c.second] + 1;
		q.push({c.first + 1, c.second});
	}
	if (c.first + 1 < n && c.second + 1 < n && grid[c.first + 1][c.second + 1] == 0) {
		grid[c.first + 1][c.second + 1] = grid[c.first][c.second] + 1;
		q.push({c.first + 1, c.second + 1});
	}
}

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
	int n = grid.size();
	if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
		return -1;
	queue<cell> q;
	q.push({0, 0}); grid[0][0] = 1;
	while (!q.empty()) {
		cell c = q.front();
		if (c.first == n - 1 && c.second == n - 1)
			return grid[n - 1][n - 1];
		move8way(grid, q, c, n);
        q.pop();
	}
	if (grid[n - 1][n - 1] == 0)
		return -1;
	return grid[n - 1][n - 1];
}