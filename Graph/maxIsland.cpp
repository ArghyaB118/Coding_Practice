/* LC#695
 
 You are given an m x n binary matrix grid. 
 An island is a group of 1's (representing land) 
 connected 4-directionally (horizontal or vertical). 
 You may assume all four edges of the grid are surrounded by water.
 
 The area of an island is the number of cells 
 with a value 1 in the island.

 Return the maximum area of an island in grid. 
 If there is no island, return 0.
 
 Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
 Output: 6
 Explanation: The answer is not 11, 
 because the island must be connected 4-directionally.
 
 Input: grid = [[0,0,0,0,0,0,0,0]]
 Output: 0
 
 11000
 11000
 00011
 00011*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> Pair;

// Idea: Do depth first search when see a 1 + maintain visited array
int maxAreaOfIsland(vector<vector<int>>& grid) {
    int maxArea = 0;
    vector<vector<bool>> visited (grid.size(), vector<bool> (grid[0].size(), false));
    // cout << visited.size() << grid.size() << visited[0].size() << grid[0].size() << endl;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 1) {
                int tmp = 0;
                queue<Pair> q; q.push({i, j}); visited[i][j] = true;
                while (!q.empty()) {
                    Pair p = q.front(); q.pop(); tmp++;
                    cout << p.first << p.second << endl;
                    // go left
                    if (p.second > 0 && grid[p.first][p.second - 1] == 1 && visited[p.first][p.second - 1] == false) {
                        q.push({p.first, p.second - 1});
                        visited[p.first][p.second - 1] = true;
                    }
                    // go right
                    if (p.second < grid[0].size() - 1 && grid[p.first][p.second + 1] == 1 && visited[p.first][p.second + 1] == false) {
                        q.push({p.first, p.second + 1});
                        visited[p.first][p.second + 1] = true;
                    }
                    // go top
                    if (p.first > 0 && grid[p.first - 1][p.second] == 1 && visited[p.first - 1][p.second] == false) {
                        q.push({p.first - 1, p.second});
                        visited[p.first - 1][p.second] = true;
                    }
                    // go down
                    if (p.first < grid.size() - 1 && grid[p.first + 1][p.second] == 1 && visited[p.first + 1][p.second] == false) {
                        q.push({p.first + 1, p.second});
                        visited[p.first + 1][p.second] = true;
                    }
                }
                maxArea = max(maxArea, tmp);
                // cout << i << j << maxArea << endl;
            }
        }
    }
    return maxArea;
}

/* LC#827

You are given an n x n binary matrix grid. 
You are allowed to change at most one 0 to be 1.

Return the size of the largest island 
in grid after applying this operation.

An island is a 4-directionally connected group of 1s.

Input: grid = [[1,1],[1,0]]
Output: 4

Constraints:
n == grid.length
n == grid[i].length
1 <= n <= 500
grid[i][j] is either 0 or 1.
*/

typedef pair<int, int> cell;

/* if we check all cells with we get a TLE
Hence, we write a function to check
whether a cell with 0 is merging two islands.
But, it may lead us with a wrong answer
as there might be an island that is largest
without joining with any other island.
Hence, we check all cells with 0, 
where any peripheral cell is 1.*/

bool mightBeJoiner (vector<vector<int>>& grid, cell c, int n) {
    if (c.first - 1 >= 0 && grid[c.first - 1][c.second] == 1)
        return true;
    if (c.first + 1 < n && grid[c.first + 1][c.second] == 1)
        return true;
    if (c.second - 1 >= 0 && grid[c.first][c.second - 1] == 1)
        return true;
    if (c.second + 1 < n && grid[c.first][c.second + 1] == 1)
        return true;
    return false;
}

int largestIsland (vector<vector<int>>& grid)  {
    int n = grid.size();
    int max_island = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0 && mightBeJoiner(grid, {i,j}, n)) {
                queue<cell> q; q.push({i, j});
                int tmp_size = 0;
                vector<vector<bool>> visited(n, vector<bool>(n, false));
                visited[i][j] = true;
                while (!q.empty()) {
                    cell c = q.front(); q.pop();
                    tmp_size++;
                    if (c.first - 1 >= 0 && grid[c.first - 1][c.second] == 1 && !visited[c.first - 1][c.second]) {
                        q.push({c.first - 1, c.second});
                        visited[c.first - 1][c.second] = true;
                    }
                    if (c.first + 1 < n && grid[c.first + 1][c.second] == 1 && !visited[c.first + 1][c.second]) {
                        q.push({c.first + 1, c.second});
                        visited[c.first + 1][c.second] = true;
                    }
                    if (c.second - 1 >= 0 && grid[c.first][c.second - 1] == 1 && !visited[c.first][c.second - 1]) {
                        q.push({c.first, c.second - 1});
                        visited[c.first][c.second - 1] = true;
                    }
                    if (c.second + 1 < n && grid[c.first][c.second + 1] == 1 && !visited[c.first][c.second + 1]) {
                        q.push({c.first, c.second + 1});
                        visited[c.first][c.second + 1] = true;
                    }
                }
                max_island = max(max_island, tmp_size);
            }
        }
    }
    if (max_island == 0 && grid[0][0] == 1) { return n * n; }
    if (max_island == 0 && grid[0][0] == 0) { return 1; }
    return max_island;
}

int main () {
    vector<vector<int>> grid = 
    // {{1, 1}, {1, 0}};
    {{1,1,0,0,0},{1,1,0,0,0},{0,0,0,1,1},{0,0,0,1,1}};
    // {{0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},
    // {0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0},
    // {0,1,0,0,1,1,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0},
    // {0,0,0,0,0,0,0,1,1,1,0,0,0},{0,0,0,0,0,0,0,1,1,0,0,0,0}};
    // cout << maxAreaOfIsland (grid) << endl;
    cout << largestIsland(grid) << endl;
    return 0;
}
