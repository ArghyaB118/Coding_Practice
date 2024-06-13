/*
Given a floor plan, 
which includes the rooms ('O'), 
the obstacles ('X') and a robot vacuum ('R'), 
your goal is to return the set of rooms 
that are farthest from the robot vacuum 
(when the robot takes the shortest path). 
The robot vacuum only move vertically 
and horizontally (not diagonally). 
So for instance an example floor plan is:

O O O O O
O O O O O
O O X O O
O R X O O
O O X O X

For which the answers include 
(4, 3) and (3, 4) 
(i.e the two tiles 
in the bottom right corner) 
having the distance of 7.
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct cell {
  int x, y, d;
  cell(int x_, int y_, int d_) {
    x = x_;
    y = y_;
    d = d_;
  }
};

vector<vector<int>> farthestPoints 
  (vector<vector<char>> &grid, int r, int c) {
  int m = grid.size();
  int n = grid[0].size();
  if (m == 0 || n == 0)
    return {};
  queue<cell> q;
  q.push(cell(r, c, 0));
  int dist = 0;
  vector<vector<int>> result;
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  visited[r][c] = true;
  while (!q.empty()) {
    cell tmp = q.front();
    cout << tmp.x << " " << tmp.y << " " << tmp.d << endl;
    q.pop();
    if (tmp.d > dist) {
      result.clear();
      result.push_back({tmp.x, tmp.y});
      dist = tmp.d;
    }
    else if (tmp.d == dist) {
      result.push_back({tmp.x, tmp.y});
    }

    if (tmp.x > 0 
      && grid[tmp.x - 1][tmp.y] == 'O' 
      && !visited[tmp.x - 1][tmp.y]) {
      q.push(cell(tmp.x - 1, tmp.y, tmp.d + 1));
      visited[tmp.x - 1][tmp.y] = true;
    }
    if (tmp.x < m - 1 
      && grid[tmp.x + 1][tmp.y] == 'O' 
      && !visited[tmp.x + 1][tmp.y]) {
      q.push(cell(tmp.x + 1, tmp.y, tmp.d + 1));
      visited[tmp.x + 1][tmp.y] = true;
    }

    if (tmp.y > 0 
      && grid[tmp.x][tmp.y - 1] == 'O' 
      && !visited[tmp.x][tmp.y - 1]) {
      q.push(cell(tmp.x, tmp.y - 1, tmp.d + 1));
      visited[tmp.x][tmp.y - 1] = true;
    }
    if (tmp.y < n - 1 
      && grid[tmp.x][tmp.y + 1] == 'O' 
      && !visited[tmp.x][tmp.y + 1]) {
      q.push(cell(tmp.x, tmp.y + 1, tmp.d + 1));
      visited[tmp.x][tmp.y + 1] = true;
    }
  }
  return result;
}

int main () {
  vector<vector<char>> grid 
  = {{'O', 'O', 'O', 'O', 'O'}, {'O', 'O', 'O', 'O', 'O'}
  , {'O', 'O', 'X', 'O', 'O'}, {'O', 'R', 'X', 'O', 'O'}
  , {'O', 'O', 'X', 'O', 'X'}};
  vector<vector<int>> farthest_points = farthestPoints(grid, 3, 1);
  for (auto& i : farthest_points)
    cout << i[0] << " " << i[1] << endl;
  return 0;
}