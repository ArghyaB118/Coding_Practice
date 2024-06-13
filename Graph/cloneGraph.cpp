/* LC#133

Given a reference of a node 
in a connected undirected graph.

Return a deep copy (clone) of the graph.

Each node in the graph contains 
a value (int) and a list (List[Node]) 
of its neighbors.

Constraints:

The number of nodes in the graph 
is in the range [0, 100].

1 <= Node.val <= 100

Node.val is unique for each node.

There are no repeated edges 
and no self-loops in the graph.

The Graph is connected 
and all nodes can be visited 
starting from the given node.
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

Node* cloneGraph(Node* node) {
	if (!node)
		return NULL;
	if (node->neighbors.size() == 0) {
		Node* root = new Node(node->val);
		return root;
	}
	int rootval = node->val;
	unordered_map<int, Node*> nodes;
	queue<Node*> q;
	q.push(node);
	while (!q.empty()) {
		nodes[q.front()->val] = q.front();
		for (auto &i : q.front()->neighbors)
			nodes[i->val] = i;
		q.pop();
	}

	unordered_map<int, Node*> newnodes;
	for (auto& i : nodes) {
		Node* newnode = new Node(i.second->val);
		newnodes[i.first] = newnode;
	}

	for (auto &i : nodes) {
		for (auto &j : i.second->neighbors) {
			newnodes[i.first]->neighbors.push_back(newnodes[j->val]);
		}
	}
	return newnodes[rootval];
}

int main () {
	Node* one = new Node(1);
	Node* two = new Node(2);
	Node* three = new Node(3);
	Node* four = new Node(4);
	one->neighbors.push_back(two); one->neighbors.push_back(four);
	two->neighbors.push_back(three); two->neighbors.push_back(one);
	three->neighbors.push_back(two); three->neighbors.push_back(four);
	four->neighbors.push_back(one); four->neighbors.push_back(three);
	Node* root = cloneGraph(one);
	return -1;
}
