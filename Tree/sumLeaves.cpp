/* LC#129

You are given the root of a binary tree containing digits from 0 to 9 only.

Each root-to-leaf path in the tree represents a number.

For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
Return the total sum of all root-to-leaf numbers. 
Test cases are generated so that the answer will fit in a 32-bit integer.

A leaf node is a node with no children.

Constraints:
The number of nodes in the tree is in the range [1, 1000].
0 <= Node.val <= 9
The depth of the tree will not exceed 10.

Input: root = [1,2,3]
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.

Input: root = [4,9,0,5,1]
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<TreeNode*, vector<int>> nodepath;


// beats 100% LC users
int sumNumbers(TreeNode* root) {
	if (root == NULL)
		return 0;
	int result = 0;
	queue<nodepath> q;
	q.push({root, {root->val}});
	while (!q.empty()) {
		nodepath tmp = q.front(); q.pop();
		if (tmp.first->left == NULL && tmp.first->right == NULL) {
			int tmp2 = 0;
			for (auto & i : tmp.second) {
				tmp2 = tmp2 * 10 + i;
			}
			result += tmp2;
		}
		else {
			if (tmp.first->left != NULL) {
				nodepath tmp3 = tmp;
				tmp3.first = tmp.first->left;
				tmp3.second.push_back(tmp.first->left->val);
				q.push(tmp3);
			}
			if (tmp.first->right != NULL) {
				nodepath tmp3 = tmp;
				tmp3.first = tmp.first->right;
				tmp3.second.push_back(tmp.first->right->val);
				q.push(tmp3);
			}
		}
	}
	return result;
}
