/* LC#427

Build a quad tree
*/


// beats ~60% LC users
class Solution {
public:
    bool is_all_same (vector<vector<int>>& grid, int row, int col, int size) {
        int tmp = grid[row][col]; 
        for (int i = row; i < row + size; i++)
            for (int j = col; j < col + size; j++)
                if (grid[i][j] != tmp)
                    return false;
        return true;
    }

    Node* constructTool (vector<vector<int>>& grid, int row, int col, int size) {
        if (is_all_same(grid, row, col, size)) {
            Node* node = new Node();
            node->val = grid[row][col];
            node->isLeaf = 1;
            return node;
        }
        Node* node = new Node();
        node->val = grid[0][0];
        node->isLeaf = 0;
        node->topLeft = constructTool(grid, row, col, size / 2);
        node->topRight = constructTool(grid, row, col + size / 2, size / 2);
        node->bottomLeft = constructTool(grid, row + size / 2, col, size / 2);
        node->bottomRight = constructTool(grid, row + size / 2, col + size / 2, size / 2);
        return node;
    }

    Node* construct (vector<vector<int>>& grid) {
        int n = grid.size();
        Node* root = constructTool (grid, 0, 0, n);
        return root;
    }
};