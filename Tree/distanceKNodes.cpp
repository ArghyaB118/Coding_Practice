/* LC#863

Given the root of a binary tree, 
the value of a target node target, 
and an integer k, 
return an array of the values of all nodes 
that have a distance k from the target node.

You can return the answer in any order.

Constraints:

The number of nodes in the tree is in the range [1, 500].
0 <= Node.val <= 500
All the values Node.val are unique.
target is the value of one of the nodes in the tree.
0 <= k <= 1000
*/

typedef pair<TreeNode*, int> node_dist;
// beats ~86% LC users
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
	if (k == 0)
		return {target->val};

	TreeNode* node = root;
	queue<TreeNode*> q;
	unordered_map<TreeNode*, TreeNode*> parents;
	q.push(node);
	parents[node] = NULL;
	while (!q.empty()) {
		node = q.front();
		q.pop();
		if (node->left) {
			parents[node->left] = node;
			q.push(node->left);
		}
		if (node->right) {
			parents[node->right] = node;
			q.push(node->right);
		}
	}

	queue<node_dist> nodes;
	nodes.push({target, k});
	unordered_set<TreeNode*> visited_nodes;
	visited_nodes.insert(target);
	vector<int> result = {};

	while (!nodes.empty()) {
		node_dist nd = nodes.front();
		nodes.pop();
		if (nd.second == 0)
			result.push_back(nd.first->val);
		else if (nd.second > 0) {
			if (nd.first->left && visited_nodes.find(nd.first->left) == visited_nodes.end()) {
				nodes.push({nd.first->left, nd.second - 1});
				visited_nodes.insert(nd.first->left);
			}
			if (nd.first->right && visited_nodes.find(nd.first->right) == visited_nodes.end()) {
				nodes.push({nd.first->right, nd.second - 1});
				visited_nodes.insert(nd.first->right);
			}
			if (parents[nd.first] && visited_nodes.find(parents[nd.first]) == visited_nodes.end()) {
				nodes.push({parents[nd.first], nd.second - 1});
				visited_nodes.insert(parents[nd.first]);
			}
		}
	}

	return result;
}
