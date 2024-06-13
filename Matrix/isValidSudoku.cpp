/* LC#36

Determine if a 9 x 9 Sudoku board is valid. 
Only the filled cells need to be validated 
according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid 
must contain the digits 1-9 without repetition.

Note:
A Sudoku board (partially filled) could be valid 
but is not necessarily solvable.
Only the filled cells need to be validated 
according to the mentioned rules.
*/

// beats ~32% LC users
bool isValidSudoku(vector<vector<char>>& board) {
	unordered_set<char> s;
	vector<unordered_set<char>> rows(9, s);
	vector<unordered_set<char>> columns(9, s);
	vector<unordered_set<char>> subgrids(9, s);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != '.') {
				if (rows[i].find(board[i][j]) != rows[i].end())
					return false;
				rows[i].insert(board[i][j]);
				if (columns[j].find(board[i][j]) != columns[j].end())
					return false;
				columns[j].insert(board[i][j]);
				int k = i / 3, l = j / 3;
				if (subgrids[3*k + l].find(board[i][j]) != subgrids[3*k + l].end())
					return false;
				subgrids[3*k + l].insert(board[i][j]);
			}
		}
	}
	return true;
}