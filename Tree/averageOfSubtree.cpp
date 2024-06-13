/* LC#2265

Given the root of a binary tree, 
return the number of nodes 
where the value of the node is equal to 
the average of the values in its subtree.

Note:
The average of n elements is 
the sum of the n elements divided by n 
and rounded down to the nearest integer.

A subtree of root is a tree 
consisting of root and all of its descendants.
*/

#include <iostream>
#include <vector>
using namespace std;

int averageOfSubtreeUtil(TreeNode* root, int &count) {
	if (root->left == NULL && root->right == NULL) {
		count++;
		return root->val;
	}
	int sum = root->val;
	if (!root->left && root->right) {
		sum += averageOfSubtreeUtil(root->right, count);
		sum /= 2;
		if (sum == root->val)
			count++;
		return sum;
	}
	if (root->left && !root->right) {
		sum += averageOfSubtreeUtil(root->left, count);
		sum /= 2;
		if (sum == root->val)
			count++;
		return sum;
	}
	sum += averageOfSubtreeUtil(root->left, count);
	sum += averageOfSubtreeUtil(root->right, count);
	sum /= 3;
	if (sum == root->val)
		count++;
	return sum;
}

int averageOfSubtree(TreeNode* root) {
	int count = 0;
	averageOfSubtreeUtil(root, count);
    return count;
}