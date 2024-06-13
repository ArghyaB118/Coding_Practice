#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

// Example Tree
//		1
//		/\
//	2		3
//	/\		/\
//4		5


struct Node {
	int data;
	struct Node *left, *right; // Alternatively, struct Node* left, *right;
	Node (int data) {
		this->data = data;
		left = right = NULL;
	} 
};

// left, right, root
// 4 5 2 3 1
// T(n) = T(k) + T(n - k -1); cost = O(n)
void PostOrder (struct Node* node) {
	if (node == NULL)
		return;
	PostOrder(node->left); PostOrder(node->right);
	cout << node->data << " ";
}


// root, left, right
// 1 2 4 5 3
void PreOrder (struct Node* node) {
	if (node == NULL)
		return;
	cout << node->data << " ";
	PreOrder(node->left); PreOrder(node->right);
}

// left, root, right
// 4 2 5 1 3
void InOrder (struct Node* node) {
	if (node == NULL)
		return;
	InOrder(node->left);
	cout << node->data << " ";
	InOrder(node->right);
}

// depth of a tree
int depth (struct Node* node) {
	if (node == NULL)
		return 0;
	else {
		int ldepth = depth(node->left);
		int rdepth = depth(node->right);
		return ((ldepth > rdepth) ? (ldepth + 1) : (rdepth + 1));
	}
}

/* LC#426

Convert a Binary Search Tree 
to a sorted Circular Doubly-Linked List in place.

You can think of the left and right pointers 
as synonymous to the predecessor and successor 
pointers in a doubly-linked list. 
For a circular doubly linked list, 
the predecessor of the first element 
is the last element, 
and the successor of the last element 
is the first element.

We want to do the transformation in place. 
After the transformation, 
the left pointer of the tree node 
should point to its predecessor, 
and the right pointer 
should point to its successor. 
You should return the pointer 
to the smallest element of the linked list.
*/

void inorderTraversal (Node* node, vector<int>& v) {
	if (node->left) { inorderTraversal(node->left, v); }
	v.push_back(node->val);
	if (node->right) { inorderTraversal(node->right, v); }
}

// beats ~85% LC users
Node* treeToDoublyList (Node* root) {
	if (!root)
		return NULL;
	vector<int> inorder_traversal = {};
	inorderTraversal (root, inorder_traversal);

	vector<Node*> nodes;
	for (auto &i : inorder_traversal) {
		Node* node = new Node(i);
		nodes.push_back(node);
	}

	for (int i = 0; i < nodes.size(); i++) {
		if (i - 1 < 0)
			nodes[i]->left = nodes.back();
		else
			nodes[i]->left = nodes[i - 1];

		if (i + 1 >= nodes.size())
			nodes[i]->right = nodes[0];
		else
			nodes[i]->right = nodes[i + 1];
	}
	return nodes[0];
}

/* LC#102

 Binary tree level order traversal
 1 2 3 4 5
 Note: Time complexity for any tree traversal = O(n)
 Space complexity = O(h) = O(log n) for DFS
					= O(ceil(n / 2)) for BFS (in the worst-case)
*/

void Level (struct Node* root, int level) {
	if (root == NULL)
		return;
	if (level == 1)
		cout << root->data << " ";
	else if (level > 1) {
		Level (root->left, level - 1);
		Level (root->right, level - 1);
	}
}

// Same as BFS on Tree -- O(n)
void LevelOrder (struct Node* root) {
	int h = depth(root);
	for (int i = 1; i <= h; i++)
		Level (root, i);
}

// level order traversal using a queue
void LevelOrderQueue (struct Node* root) {
	if (root == NULL)
		return;
	queue<Node*> q; q.push(root);
	while (!q.empty()) {
		Node* node = q.front(); q.pop();
		if (node->left != NULL)
			q.push(node->left); 
		if (node->right != NULL) 
			q.push(node->right);
		cout << node->data << " ";
	}
}

// beats ~62% LC users
vector<vector<int>> levelOrder (Node* root) {
	if (!root) { return {}; }
	queue<Node*> curr_level, next_level; 
	curr_level.push(root);
	vector<vector<int>> result;
	vector<int> curr;
	while (!curr_level.empty()) {
		Node* node = curr_level.front();
		curr_level.pop();
		curr.push_back(node->val);
		if (node->left) { next_level.push(node->left); }
		if (node->right) { next_level.push(node->right); }
		if (curr_level.empty()) {
			result.push_back(curr);
			curr.clear();
			swap(curr_level, next_level);
		}
	}
	return result;
}

/* LC#314 LC#987

Vertical Order Traversal of a Binary Tree
    1
   / \
  2   3
 /\   /\
4  6 5  7

Given the root of a binary tree, calculate the vertical order traversal of the binary tree.

For each node at position (row, col), its left and right children will be 
at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. 
The root of the tree is at (0, 0).

The vertical order traversal of a binary tree is a list of 
top-to-bottom orderings for each column index starting from the 
leftmost column and ending on the rightmost column. 
There may be multiple nodes in the same row and same column. 

Option 1: LC#314
If two nodes are in the same row and column, 
the order should be from left to right.

Option 2 (difficult): LC#987
In such a case, sort these nodes by their values.

Return the vertical order traversal of the binary tree.

Input: root = [1,2,3,4,5,6,7]
Output: [[4],[2],[1,5,6],[3],[7]]

Input: root = [1,2,3,4,6,5,7]
Output: [[4],[2],[1,5,6],[3],[7]]
*/

// beats ~61% LC users
typedef pair<int, struct Node*> Pair;

vector<vector<int>> verticalOrder (struct Node* root) {
	if (root == NULL)
		return {};
	vector<vector<int>> result;
	map<int, vector<int>> elements;
	queue<Pair> nodes; nodes.push(make_pair(0, root));
	while (!nodes.empty()) {
		Pair root = nodes.front();
		elements[root.first].push_back(root.second->data);
		nodes.pop();
		if (root.second->left != NULL) {
			nodes.push(make_pair(root.first - 1, root.second->left));
		}
		if (root.second->right != NULL)
			nodes.push(make_pair(root.first + 1, root.second->right));
	}
	for (auto & m : elements) {
//		sort(m.second.begin(), m.second.end());
		result.push_back(m.second);
	}
	return result;
}

// beats 100% LC users
vector<vector<int>> verticalOrder2(TreeNode* root) {
    if (root == NULL)
	    return {};
    TreeNode* tmp = root;
    int max_depth = 0, min_depth = 0;
    queue<Pair> nodes; nodes.push(make_pair(0, tmp));
    while (!nodes.empty()) {
        Pair root = nodes.front();
        min_depth = min(min_depth, root.first);
        max_depth = max(max_depth, root.first);
	    nodes.pop();
        if (root.second->left != NULL) {
            nodes.push(make_pair(root.first - 1, root.second->left));
        }
        if (root.second->right != NULL)
            nodes.push(make_pair(root.first + 1, root.second->right));
    }
    vector<vector<int>> result(max_depth - min_depth + 1, vector<int>{});
    
    nodes.push(make_pair(0, root));
    while (!nodes.empty()) {
        Pair root = nodes.front();
        result[root.first - min_depth].push_back(root.second->val);
        nodes.pop();
        if (root.second->left != NULL) {
            nodes.push(make_pair(root.first - 1, root.second->left));
        }
        if (root.second->right != NULL)
            nodes.push(make_pair(root.first + 1, root.second->right));
    }
	return result;
}


// beats 100% LC users
struct elt {
	int row, col;
	TreeNode* node;
	elt(int row_, int col_, TreeNode* node_) {
		row = row_; col = col_; node = node_;
	}
};

static bool cmp (const elt &e1, const elt &e2) {
	if (e1.row == e2.row)
		return e1.node->val < e2.node->val;
	return e1.row < e2.row;
}

vector<vector<int>> verticalTraversal (TreeNode* root) {
	if (root == NULL)
		return {};
	vector<vector<int>> result;
	map<int, vector<elt>> elements;
	queue<elt> nodes; 
	nodes.push(elt(0, 0, root));
	while (!nodes.empty()) {
		elt node = nodes.front();
		elements[node.col].push_back(node);
		nodes.pop();
		if (node.node->left) {
			nodes.push(elt(node.row + 1, node.col - 1, node.node->left));
		}
		if (node.node->right) {
			nodes.push(elt(node.row + 1, node.col + 1, node.node->right));
		}
	}
	for (auto &m : elements) {
		sort(m.second.begin(), m.second.end(), cmp);
		vector<int> tmp = {};
		for (auto &i : m.second)
			tmp.push_back(i.node->val);
		result.push_back(tmp);
	}
	return result;
}

Node* array2LevelOrderTree (int arr[], Node* root, int l, int r) {
	if (l < r) {
		Node* temp = new Node(arr[l]);
		root = temp;
		root->left = array2LevelOrderTree (arr, root->left, 2*l + 1, r);
		root->right = array2LevelOrderTree (arr, root->right, 2*l + 2, r);
	}
	return root;
}

/* LC#543

Given the root of a binary tree, 
return the length of the diameter of the tree.

The diameter of a binary tree is the length 
of the longest path between any two nodes in a tree. 
This path may or may not pass through the root.

The length of a path between two nodes 
is represented by the number of edges between them.

Input: root = [1,2,3,4,5]
Output: 3

Input: root = [1,2]
Output: 1
*/

int diameter (struct Node* root) {
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 0;
	if (root->left == NULL)
		return max(depth(root->right), diameter(root->right));
	if (root->right == NULL)
		return max(depth(root->left), diameter(root->left));
	return (diameter(root->left) > diameter(root->right)) 
			? max(diameter(root->left), depth(root->left) + depth(root->right))
			: max(diameter(root->right), depth(root->left) + depth(root->right));
}

void getDepths (struct Node* node, unordered_map<Node*, int>& depth_of_nodes) {
	if (node->left && depth_of_nodes.find(node->left) == depth_of_nodes.end())
		getDepths(node->left, depth_of_nodes);
	if (node->right && depth_of_nodes.find(node->right) == depth_of_nodes.end())
		getDepths(node->right, depth_of_nodes);
	if (node->left && node->right)
		depth_of_nodes[node] = max(depth_of_nodes[node->left], depth_of_nodes[node->left]) + 1;
	else if (node->left && !node->right)
		depth_of_nodes[node] = depth_of_nodes[node->left] + 1;
	else if (!node->left && node->right)
		depth_of_nodes[node] = depth_of_nodes[node->right] + 1;
	else if (!node->left && !node->right)
		depth_of_nodes[node] = 1;
}

int diameterUtil (struct Node* root, unordered_map<Node*, int>& depth_of_nodes) {
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 0;
	if (root->left == NULL)
		return max(depth_of_nodes[root->right], diameterUtil(root->right, depth_of_nodes));
	if (root->right == NULL)
		return max(depth_of_nodes[root->left], diameterUtil(root->left, depth_of_nodes));
	int diameterL = diameterUtil(root->left, depth_of_nodes);
	int diameterR = diameterUtil(root->right, depth_of_nodes);
	return (diameterL > diameterR) 
			? max(diameterL, depth_of_nodes[root->left] + depth_of_nodes[root->right])
			: max(diameterR, depth_of_nodes[root->left] + depth_of_nodes[root->right]);
}

int diameterOpt (struct Node* root) {
	unordered_map<Node*, int> depth_of_nodes;
	getDepths (root, depth_of_nodes);
	return diameterUtil(root, depth_of_nodes);
}

/* LC#124

Binary Tree Maximum Path Sum
A path in a binary tree is a sequence 
of nodes where each pair of adjacent nodes 
in the sequence has an edge connecting them. 
A node can only appear in the sequence at most once. 
Note that the path does not need 
to pass through the root.

The path sum of a path 
is the sum of the node's values in the path.

Given the root of a binary tree, 
return the maximum path sum of any non-empty path.
*/

void pathSums (TreeNode* node, unordered_map<TreeNode*, vector<int>>& path_sums) {
	if (node->left && path_sums.find(node->left) == path_sums.end()) {
		pathSums(node->left, path_sums);
	}
	if (node->right && path_sums.find(node->right) == path_sums.end()) {
		pathSums(node->right, path_sums);
	}
    path_sums[node] = {0, 0};
	if (!node->left) {
		path_sums[node][0] = node->val;
	}
	else {
		path_sums[node][0] = max(path_sums[node->left][0], path_sums[node->left][1]) + node->val;
	}

	if (!node->right) {
		path_sums[node][1] = node->val;
	}
	else {
		path_sums[node][1] = max(path_sums[node->right][0], path_sums[node->right][1]) + node->val;
	}
}

int maxPathSum(TreeNode* root) {
    if (!root)
        return 0;
	unordered_map<TreeNode*, vector<int>> path_sums;
	pathSums (root, path_sums);
	queue<TreeNode*> q;
	q.push(root);
	int max_path_sum = INT_MIN;
	while (!q.empty()) {
		TreeNode* tmp = q.front();
		q.pop();
		if (tmp->left) { q.push(tmp->left); }
		if (tmp->right) { q.push(tmp->right); }
		max_path_sum = max(max_path_sum, path_sums[tmp][0] + path_sums[tmp][1] - tmp->val);
	}
	return max_path_sum;
}

/* LC#1245

The diameter of a tree is 
the number of edges in the longest path in that tree.

There is an undirected tree of n nodes 
labeled from 0 to n - 1. 
You are given a 2D array edges where edges.length == n - 1 
and edges[i] = [ai, bi] indicates that 
there is an undirected edge between nodes ai and bi in the tree.

Return the diameter of the tree.
*/

typedef pair<int, int> path_length;

// TLE
int treeDiameter(vector<vector<int>>& edges) {
	unordered_map<int, vector<int>> adj;
    int n = 0;
	for (auto &edge : edges) {
		if (adj.find(edge[0]) != adj.end())
			adj[edge[0]].push_back(edge[1]);
		else
			adj[edge[0]] = {edge[1]};
		if (adj.find(edge[1]) != adj.end())
			adj[edge[1]].push_back(edge[0]);
		else
			adj[edge[1]] = {edge[0]};
        n = max(n, edge[0]);
        n = max(n, edge[1]);
	}
	int count = 0;
	for (auto &i : adj) {
        vector<bool> visited(n + 1, false);
		queue<path_length> q;
		q.push({i.first, 0});
        visited[i.first] = true;
		while (!q.empty()) {
			path_length tmp = q.front();
			count = max(count, tmp.second);
			q.pop();
			for (auto& j : adj[tmp.first]) {
                if (!visited[j]) {
    				q.push({j, tmp.second + 1});
                    visited[j] = true;
                }
			}
		}
	}
	return count;
}


/* LC#1161

Given the root of a binary tree, 
the level of its root is 1, 
the level of its children is 2, and so on.

Return the smallest level x 
such that the sum of all the values 
of nodes at level x is maximal.
*/

// beats ~92% LC users
int maxLevelSum(TreeNode* root) {
	int sum = -100001, level = 1, max_level = 0, tmp_sum = 0;
	queue<TreeNode*> curr_level, next_level;
	curr_level.push(root);
	while (!curr_level.empty()) {
		TreeNode* tmp = curr_level.front();
		tmp_sum += tmp->val;
		curr_level.pop();
		if (tmp->left) { next_level.push(tmp->left); }
		if (tmp->right) { next_level.push(tmp->right); }
		if (curr_level.empty()) {
			if (tmp_sum > sum) { max_level = level; }
			sum = max(sum, tmp_sum);
			tmp_sum = 0;
			level++;
			swap(curr_level, next_level);
		}
	}
	return max_level;
}

/* LC#199

Given the root of a binary tree, 
imagine yourself standing on the right side of it, 
return the values of the nodes you can see 
ordered from top to bottom.

Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]
*/

// beats 65% LC users
vector<int> rightSideView(TreeNode* root) {
	vector<int> right_projection;
	if (!root) { return right_projection; }
	queue<TreeNode*> curr, next;
	curr.push(root);
	while (!curr.empty()) {
		TreeNode* node = curr.front();
		if (curr.size() == 1)
			right_projection.push_back(node->val);
		curr.pop();
		if (node->left) { next.push(node->left); }
		if (node->right) { next.push(node->right); }
		if (curr.empty()) { swap(curr, next); }
	}
	return right_projection;
}

// WRONG! root = [1,2,3,4] expected = [1,3,4] output = [1, 3]
vector<int> rightSideView2 (struct Node* root) {
	vector<int> v;
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* root = q.front();
		v.push_back(root->data);
		q.pop();
		if (root->right != NULL) {
			q.push(root->right);
			root = root->right;
		}
		else if (root->right == NULL && root->left != NULL) {
			q.push(root->left);
			root = root->left;
		}
	}
	return v;
}

/* LC#103

Zigzag order traversal of a tree:
    1
   / \
  2   3
 /\   /\
4  5 6  7
	   / \
	  8   9

Output: 1, 3, 2, 4, 5, 6, 7, 9, 8
*/

vector<int> zigzagOrder (struct Node* root) {
	vector<vector<int>> traversal;
	queue<Pair> q; q.push(make_pair(0, root));
	int d = depth(root);
	for (int i = 0; i < d; i++)
		traversal.push_back({});
	while (!q.empty()) {
		Pair p = q.front();
		q.pop();
		traversal[p.first].push_back(p.second->data);
		if (p.second->left)	
			q.push(make_pair(p.first + 1, p.second->left));
		if (p.second->right)
			q.push(make_pair(p.first + 1, p.second->right));
	}
	vector<int> result;
	bool reverse = false;
	for (int i = 0; i < traversal.size(); i++) {
		if (!reverse) {
			reverse = true;
			for (int j = 0; j < traversal[i].size(); j++)
				result.push_back(traversal[i][j]);
		}
		else {
			reverse = false;
			for (int j = traversal[i].size() - 1; j >= 0; j--)
				result.push_back(traversal[i][j]);
		}
	}
	return result;
}

int main() {
	struct Node *root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->left = new Node(4);
	root->left->right = new Node(5);
	root->right->left = new Node(6);
	root->right->right = new Node(7);
	PostOrder(root); cout << endl; 
	PreOrder(root); cout << endl; 
	InOrder(root); cout << endl; 
	LevelOrder(root); cout << endl;
	LevelOrderQueue(root); cout << endl;

	int arr[] = {1, 2, 3, 4, 5}; int n = sizeof(arr) / sizeof(arr[0]);
	struct Node* new_root = array2LevelOrderTree (arr, new_root, 0, n);
	LevelOrder(new_root); cout << endl;

	int arr_preorder[] = {1, 2, 4, 5, 3};
	int arr_inorder[] = {4, 2, 5, 1, 3};
//	struct Node* root = array2InPreOrderTree(arr_inorder, arr_preorder);
	LevelOrder(new_root); cout << endl;


	vector<vector<int>> result = verticalOrder(root);
	cout << "Vertical Order Traversal: ";
	for (int i = 0; i < result.size(); i++) {
		cout << "{";
		for (int j = 0; j < result[i].size(); j++)
			cout << result[i][j] << ",";
		cout << "}";
	}
	cout << endl;

	cout << "The diameter of the tree: " << diameter(root) << endl;
	
	vector<int> v = rightSideView(root);
	for (int & vv : v)
		cout << vv << " ";
	cout << endl;

	root->right->right->left = new Node(8);
	root->right->right->right = new Node(9);
	vector<int> zigzag = zigzagOrder(root);
	cout << "The zigzag order traversal is: ";
	for (int & z : zigzag)
		cout << z << " ";
	cout << endl;
	return 0;
}
