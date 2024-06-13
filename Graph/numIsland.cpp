/* LC#200

Given an m x n 2D binary grid grid 
which represents a map of '1's (land) and '0's (water), 
return the number of islands.

An island is surrounded by water 
and is formed by connecting adjacent lands 
horizontally or vertically. 
You may assume all four edges of the grid 
are all surrounded by water.
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
typedef pair<int, int> pt;

bool allVisited (vector<vector<char>>& grid) {
	for (auto& row : grid) {
		for (auto& cell : row) {
			if (cell == '1') {
				return false;
			}
		}
	}
	return true;
}

int numOfOnes(vector<vector<char>>& grid) {
	int num = 0;
	for (auto& row : grid) {
		for (auto& cell : row) {
			if (cell == '1') {
				num++;
			}
		}
	}
	return num;
}

int numIslands2(vector<vector<char>>& grid) {
	int num = 0;
	queue<pt> q;
	int n = numOfOnes (grid), m = 0;
	while (m < n) { // (true) {
		// if (allVisited(grid))
		// 	return num;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				if (grid[i][j] == '1') {
					q.push({i, j}); num++;
					while (!q.empty()) {
						pt p = q.front(); q.pop(); m++;
						int x = p.first, y = p.second;
						grid[x][y] = '2'; // '2' means visited.
						if (x + 1 < grid.size() && grid[x + 1][y] == '1')
							q.push({x + 1, y});
						if (y + 1 < grid[0].size() && grid[x][y + 1] == '1')
							q.push({x, y + 1});
						if (y - 1 >= 0 && grid[x][y - 1] == '1')
							q.push({x, y - 1});
						if (x - 1 >= 0 && grid[x - 1][y] == '1')
							q.push({x - 1, y});
					}
				}
			}
		}
	}
	return num;
}

// beats ~55% LC users
int numIslands(vector<vector<char>>& grid) {
	int m = grid.size();
	int n = grid[0].size();
	int num_islands = 0;
	vector<vector<bool>> visited(m, vector<bool>(n, false));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == '1' && !visited[i][j]) {
				num_islands++;
				queue<pt> q; q.push({i, j});
				visited[i][j] = true;
				while (!q.empty()) {
					pt p = q.front(); q.pop();
					if (p.first + 1 < m && grid[p.first + 1][p.second] == '1' && !visited[p.first + 1][p.second]) {
						q.push({p.first + 1, p.second});
						visited[p.first + 1][p.second] = true;
					}
					if (p.second + 1 < n && grid[p.first][p.second + 1] == '1' && !visited[p.first][p.second + 1]) {
						q.push({p.first, p.second + 1});
						visited[p.first][p.second + 1] = true;
					}

					if (p.first - 1 >= 0 && grid[p.first - 1][p.second] == '1' && !visited[p.first - 1][p.second]) {
						q.push({p.first - 1, p.second});
						visited[p.first - 1][p.second] = true;
					}
					if (p.second - 1 >= 0 && grid[p.first][p.second - 1] == '1' && !visited[p.first][p.second - 1]) {
						q.push({p.first, p.second - 1});
						visited[p.first][p.second - 1] = true;
					}
				}
			}
		}
	}
	return num_islands;
}

int main () {
	vector<vector<char>> grid = 
	{{'1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','0','1','1'},
	{'0','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','0'},
	{'1','0','1','1','1','0','0','1','1','0','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','0','1','1','1','1','1','1','0','1','1','1','0','1','1','1','0','1','1','1'},
	{'0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','0','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','0','1','1','1','1','1','1','1','0','1','1','1','1','1','1'},
	{'1','0','1','1','1','1','1','0','1','1','1','0','1','1','1','1','0','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','0'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','0','0'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}};
	cout << numIslands(grid) << endl;
	return 0;
}