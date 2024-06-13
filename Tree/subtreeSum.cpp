/* LC#508

Most frequent subtree sum

Given the root of a binary tree, 
return the most frequent subtree sum. 
If there is a tie, 
return all the values with the highest frequency in any order.

The subtree sum of a node is defined 
as the sum of all the node values 
formed by the subtree rooted at that node 
(including the node itself).
*/

#include <iostream>
#include <unordered_map>
#include <vector>

// beats 75% LC users
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int get_subtree_sum (TreeNode* root, unordered_map<int, int>& count) {
	if (!root->left && !root->right) {
		int sum = root->val;
		count[sum]++;
		return sum;
	}
	else if (!root->left) {
		int sum = root->val + get_subtree_sum(root->right, count);
		count[sum]++;
		return sum;
	}
	else if (!root->right) {
		int sum = root->val + get_subtree_sum(root->left, count);
		count[sum]++;
		return sum;
	}
	else {
		int sum = root->val 
			+ get_subtree_sum(root->right, count) 
			+ get_subtree_sum(root->left, count);
		count[sum]++;
		return sum;
	}
	return -1;
}

vector<int> findFrequentTreeSum(TreeNode* root) {
	vector<int> result;
	unordered_map<int, int> count;
	get_subtree_sum(root, count);
    int tmp_count = 0;
	for (auto &i : count) {
		if (i.second > tmp_count) {
			result.clear();
			result.push_back(i.first);
			tmp_count = i.second;
		}
		else if (i.second == tmp_count) {
			result.push_back(i.first);
		}
	}
    return result;
}

int main () {
	
	return 0;
}