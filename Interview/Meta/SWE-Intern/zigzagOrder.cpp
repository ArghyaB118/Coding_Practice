/*
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

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
	int data;
	struct Node *left, *right; // Alternatively, struct Node* left, *right;
	Node (int data) {
		this->data = data;
		left = right = NULL;
	} 
};
typedef pair<int, struct Node*> Pair;
int depth (struct Node* node) {
	if (node == NULL)
		return 0;
	else {
		int ldepth = depth(node->left);
		int rdepth = depth(node->right);
		return ((ldepth > rdepth) ? (ldepth + 1) : (rdepth + 1));
	}
}


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
	root->right->right->left = new Node(8);
	root->right->right->right = new Node(9);
	vector<int> zigzag = zigzagOrder(root);
	cout << "The zigzag order traversal is: ";
	for (int & z : zigzag)
		cout << z << " ";
	cout << endl;
	return 0;
}
