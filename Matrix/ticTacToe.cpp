/* LC#348

Assume the following rules are for the tic-tac-toe game 
on an n x n board between two players:

A move is guaranteed to be valid 
and is placed on an empty block.
Once a winning condition is reached, 
no more moves are allowed.
A player who succeeds in placing n 
of their marks in a horizontal, vertical, 
or diagonal row wins the game.
Implement the TicTacToe class:

TicTacToe(int n) 
Initializes the object the size of the board n.
int move(int row, int col, int player) 
Indicates that the player with id player plays 
at the cell (row, col) of the board. 
The move is guaranteed to be a valid move, 
and the two players alternate in making moves. 

Return
0 if there is no winner after the move,
1 if player 1 is the winner after the move, or
2 if player 2 is the winner after the move.
*/

#include <iostream>
#include <vector>
using namespace std;

// beats ~30% LC users
class TicTacToe {
private:
    int n;
    vector<vector<int>> mat;
public:
    TicTacToe(int n) {
        this->n = n;
        vector<int> tmp(this->n, 0);
        for (int i = 0; i < this->n; i++)
            this->mat.push_back(tmp);
    }
    
    int winnercheck () {
        // row check
        int x = mat[0][0];
        bool ret = true;
        for (int i = 0; i < n; i++) {
            x = mat[i][0];
            ret = true;
            if (x != 0) {
                for (int j = 0; j < n; j++) {
                    if (mat[i][j] != x) {
                        ret = false;
                        break;
                    }
                }
                if (ret) { return x; }
            }
        }
        // cout << "x" << endl;
        // diagonal check
        x = mat[0][0];
        ret = true;
        if (x > 0) {
            for (int i = 0; i < n; i++) {
                if (mat[i][i] != x) {
                    ret = false;
                    break;
                }
            }
        }
        if (ret && x != 0) { return x; }
        // cout << "y" << endl;
        // reverse diagonal check
        x = mat[n - 1][0];
        ret = true;
        for (int i = 0; i < n; i++) {
            if (mat[n - i - 1][i] != x) {
                ret = false;
                break;
            }
        }
        if (ret && x != 0) { return x; }
        // cout << "z" << endl;
        // column check
        for (int i = 0; i < n; i++) {
            x = mat[0][i];
            ret = true;
            if (x != 0) {
                for (int j = 0; j < n; j++) {
                    if (mat[j][i] != x) {
                        ret = false;
                        break;
                    }
                }
                if (ret) { return x; }
            }
        }
        // cout << "p" << endl;
        return 0;
    }
    
    
    int move(int row, int col, int player) {
        mat[row][col] = player;
        return winnercheck();
    }
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */

int main () {
    TicTacToe t = TicTacToe(3);
    cout << t.move(0, 0, 1) << t.move(0, 2, 2) << t.move(2, 2, 1) << endl;
    cout << t.move(1, 1, 2) << t.move(2, 0, 1) << t.move(1, 0, 2) << t.move(2, 1, 1) << endl;
    return 0;
}