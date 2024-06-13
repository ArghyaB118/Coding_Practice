/* LC#51

The n-queens puzzle is the problem 
of placing n queens on an n x n chessboard 
such that no two queens attack each other.

Given an integer n, 
return all distinct solutions 
to the n-queens puzzle. 
You may return the answer in any order.

Each solution contains a distinct board configuration 
of the n-queens' placement, 
where 'Q' and '.' both indicate 
a queen and an empty space, respectively.
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

vector<vector<string>> solveNQueens(int n) {
	vector<vector<string>> result;
	string row = "";
	row.append(n, '.');
	vector<string> board(n, row);
	queue<vector<string>> q;
	for (int i = 0; i < n; i++) {
		vector<string> tmp = board;
		tmp[0][i] = 'Q';
		q.push(tmp);
	}
	int i = 1;
	while (!q.empty() && i < n) {
		vector<string> tmp = q.front();
		q.pop();
		for (int j = 0; j < n; j++) {
			bool can_place_queen = true;
			vector<string> tmp_copy = tmp;
			for (int k = 0; k <= i; k++) {
				if (tmp_copy[k][j] == 'Q')
					can_place_queen = false;
			}
			if (can_place_queen) {
				int k = i, l = j;
				while (k >= 0 && l >= 0) {
					if (tmp_copy[k][l] == 'Q')
						can_place_queen = false;
					k--; l--;
				}
			}
			if (can_place_queen) {
				int k = i, l = j;
				while (k >= 0 && l < n) {
					if (tmp_copy[k][l] == 'Q')
						can_place_queen = false;
					k--; l++;
				}
			}
			if (can_place_queen) {
				tmp_copy[i][j] = 'Q';
				if (i == n - 1)
					result.push_back(tmp_copy);
				else
					q.push(tmp_copy);
			}
		}
		i++;
	}
	return result;
}

int main () {
	int n = 4;
	solveNQueens(n);
}