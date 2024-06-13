/* LC#2812

You are given a 0-indexed 2D matrix grid 
of size n x n, where (r, c) represents:

A cell containing a thief if grid[r][c] = 1
An empty cell if grid[r][c] = 0
You are initially positioned at cell (0, 0). 

In one move, 
you can move to any adjacent cell in the grid, 
including cells containing thieves.

The safeness factor of a path on the grid 
is defined as the minimum manhattan distance 
from any cell in the path to any thief in the grid.

Return the maximum safeness factor 
of all paths leading to cell (n - 1, n - 1).

An adjacent cell of cell (r, c), 
is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) 
and (r - 1, c) if it exists.

The Manhattan distance between two cells 
(a, b) and (x, y) is equal to |a - x| + |b - y|, 
where |val| denotes the absolute value of val.
*/

#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> cell;

class path {
public:
	vector<vector<bool>> visited;
	cell p;
	int n, safeness;
	path(int i_, int j_, int n_) {
		this->p.first = i_;
		this->p.second = j_;
		this->n = n_;
		vector<bool> v(n, false);
		for (int i = 0; i < n; i++)
			visited.push_back(v);
		visited[this->p.first ][this->p.second] = true;
	}
};

int minDistance (vector<vector<int>>& grid, vector<cell>& theives, cell p) {

}

int maximumSafenessFactor(vector<vector<int>>& grid) {
	int n = grid.size();
	if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
		return 0;
	vector<cell> theives;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			thieves.push_back({i, j});


	path p = path(0, 0, n);
	queue<path> q;
	while (!q.empty()) {

	}
	return 0;
}

int main () {
	vector<vector<int>> grid = {{1,0,0},{0,0,0},{0,0,1}};
	cout << maximumSafenessFactor(grid) << endl;
	return 0;
}