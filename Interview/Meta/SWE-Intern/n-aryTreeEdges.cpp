/*
Problem: Given a tree, return the minimum number of edges you need to travel
in order to visit all the nodes with X.

             Start
            /  |  \
           X   .   .
          /   / \   \
         .   X   X   X
        / \     / \   \
       .   .   X   .   .
          /|\
         . . X

left: 8
middle: 8
right: 4
return total: 20
  

  Start
    |2
    . 
   2|\ 2
    x x

  Start
    |
    .
    |
    .

  Start
    |
    x
    |
    .

node {
  children
  value: bool
}
*/

#include <iostream>
using namespace std;

struct node {
  bool val;
  struct node *left, *middle, *right; 
  node (bool val) {
    this->val = val;
    left = middle = right = nullptr;
  }
};


int numOfEdges (node * root) {
  if (root == NULL)
    return 0;
  if (root->left == NULL && root->middle == NULL && root->right == NULL) {
    if (root->val == true)
      return 2;
    else
      return 0;
  }
  if (numOfEdges(root->left) + numOfEdges(root->middle) + numOfEdges(root->right) != 0)
    return 2 + numOfEdges(root->left) + numOfEdges(root->middle) + numOfEdges(root->right);
  return 0;
}

int main () {
  struct node *root = new node(true);
  root->middle = new node(false);
  root->middle = new node(true);
  root->right = new node(true);
  cout << numOfEdges(root) << endl;
  return 0;
}

/*
int numOfNodes (node * root, int currentDepth) {
  if (root == NULL)
    return 0;
  if (node->val == true)
    return 2* currentDepth + numOfNodes(root->left, currentDepth + 1) + numOfNodes(root->middle, currentDepth + 1) + numOfNodes(root->right, currentDepth + 1);
  return numOfNodes(root->left, currentDepth + 1) + numOfNodes(root->middle, currentDepth + 1) + numOfNodes(root->right, currentDepth + 1);
}


// numOfNodes(root, 0);

