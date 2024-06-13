//
//  interviewGoogle.cpp
//  
//
//  Created by Arghya Bhattacharya on 11/7/22.
//

#include <stdio.h>
/* 
You're given an interface of a Dynamic Tree, 
your task is to write an implementation 
according to the interface docstrings.
You can change the syntax 
according to a language of your choice, 
feel free to use any helper methods or fields. 
*/

// Implement the methods of the following Tree class.
struct TreeNode {
  TreeNode* parent;
  // New fields if required.
  TreeNode() : parent(nullptr) {}
};

// The tree will always have a non-empty root node inside it.
class Tree {
 public:
  // Creates Tree instance in which the number of nodes can not exceed capacity and the root node is created.
  // 1 <= # of nodes < 1B <= capacity
  Tree(int capacity) : root_(new TreeNode()), capacity_(capacity) {
    this->nodes.push_back(this->root_);
  }

  // Creates a node that is 
  // attached to a parent node 
  // that is guaranteed to already exist in the Tree.
  TreeNode* createNode(TreeNode* parent) {
    if (this->nodes.size() == capacity)
      return NULL;
    // To be implemented.
    struct TreeNode* tmp = new TreeNode;
    tmp->parent = parent;
    this-nodes.push_back(tmp);
    return tmp;
  }

  // Returns a random node in the Tree. 
  // Each node in the Tree has an equal probability to be selected.
  TreeNode* getRandomNode() {
    // To be implemented.
    int currSize = this->nodes.size();
    int rand = rand() % (currSize); // 0 -- currSize - 1
    return this->nodes[rand];
  }

 private:
  int capacity_;
  TreeNode* root_;
  vector<TreeNode*> nodes;
  // New fields if required.
};




// 0
// 1 2 3
// 4 5, 6, 7, 8

// 9

// 0
// 1 2 3
// 4 5, 6 9, 7, 8


// You're given an interface of a Dynamic Tree, your task is to write an implementation according to the interface docstrings.
// You can change the syntax according to a language of your choice, feel free to use any helper methods or fields.

// Implement the methods of the following Tree class.
struct TreeNode {
  TreeNode* parent;
  // New fields if required.
  TreeNode() : parent(nullptr) {}
};

// The tree will always have a non-empty root node inside it.
class Tree {
 public:
  // Creates Tree instance in which the number of nodes can not exceed capacity and the root node is created.
  // 1 <= # of nodes < 1B <= capacity
  Tree(int capacity) : root_(new TreeNode()), capacity_(capacity) {
    this->nodes.push_back(this->root_);
    this->leaves.push_back(this->root_);
    this->leaveSet.insert(this->root_);
  }

  // Creates a node that is attached to a parent node that is guaranteed to already exist in the Tree.
  TreeNode* createNode(TreeNode* parent) {
    if (this->nodes.size() == capacity)
      return NULL;
    // To be implemented.
    struct TreeNode* tmp = new TreeNode;
    tmp->parent = parent;
    this-nodes.push_back(tmp);
    
    // change goes here
    this->leaves.push_back(tmp);
    this->leaveSet.push_back(tmp);
    // if (find (leaves.begin(), leaves.end(), parent) != leaves.end())
       // leaves.erase(parent);
    if (leaveSet.find(parent) != leave.end())
      leaveSet.erase(parent);
    
    return tmp;
  }

  // Returns a random node in the Tree. Each node in the Tree has an equal probability to be selected.
  TreeNode* getRandomNode() {
    // To be implemented.
    int currSize = this->nodes.size();
    int rand = rand() % (currSize); // 0 -- currSize - 1
    return this->nodes[rand];
  }
  
  // Returns a random leaf in the Tree. Each leaf in the Tree has an equal probability to be selected.
  TreeNode* getRandomLeaf() {
    int currLeafSize = this->leaves.size();
    int rand = rand() % (currLeafSize); // 0 -- currLeafSize - 1
    return this->leaves[rand];
  }

 private:
  int capacity_;
  TreeNode* root_;
  vector<TreeNode*> nodes;
  vector<TreeNode*> leaves;
  unordered_set<TreeNodes*> leaveSet;
  // New fields if required.
};




// 0
// 1 2 3
// 4 5, 6, 7, 8

// 9

// 0
// 1 2 3
// 4 5, 6 9, 7, 8

// 1 2 3 4
// 1 2 3




Question: Match string against a list of prefixes.

Input: 1) a list of string prefixes (frozen constant list given at the job startup, O(100)).
       2) many target strings to match, billions of them.
Output: returns true if and only if one prefix in the list matches the target string as a prefix.

Example:
prefixes = ["aa", "bb", "cc"]
target = "aaa" -> returns true
target = "ddd" -> returns false
target = "aa" -> returns true
target = "a" -> returns false

  // Idea 0: to iterate over all the prefixes and compare, O(# prefixes)
  // Idea 1: put all prefix in a hashtable and incrementally append one char from target at a time
  //         and check against the hashtable. Complexity bound by O(max(|prefix|) * (1+load_factor))
  // Idea 2: Trie built from the prefixes. O(max(|prefix|))
 
struct Node {
  char c;
  struct Node *children[256];
}
class Trie {
  // initiated
  Node* root;
  //
  void insert(string s) {... };
  
  bool prefixMatch (string target) {
    int idx = 0;
    Node* node = this->root;
    while (idx < target.length()) {
      bool tmp = false;
      if node->children[target[idx]] == target[idx]
        tmp = true;
      if (tmp) {
        node = node->children[target[idx]];
        idx++;
      }
      else {
        return false;
      }
    }
    return true;
  }
};
  
  
  

abcdef
abcxyz

abc

xyz def



Question: Match string against a list of prefixes.

Input: 1) a list of string prefixes (frozen constant list given at the job startup, O(100)).
       2) many target strings to match, billions of them.
Output: returns true if and only if one prefix in the list matches the target string as a prefix.

Example:
prefixes = ["aa", "bb", "cc"]
target = "aaa" -> returns true
target = "ddd" -> returns false
target = "aa" -> returns true
target = "a" -> returns false

  // Idea 0: to iterate over all the prefixes and compare, O(# prefixes)
  // Idea 1: put all prefix in a hashtable and incrementally append one char from target at a time
  //         and check against the hashtable. Complexity bound by O(max(|prefix|) * (1+load_factor))
  // Idea 2: Trie built from the prefixes. O(max(|prefix|))
 
struct Node {
  char c;
  struct Node *children[256];
  bool leaf;
}
class Trie {
  // initiated
  Node* root;
  //
  void insert(string s) {
    
  }
  
  bool prefixMatch (string target) {
    int idx = 0;
    Node* node = this->root;
    if (node == NULL)
      return true;
    while (idx < target.length()) {
      if (leaf)
        return true;
      else if (!leaf && node->childres[target[idx]] == NULL)
        return false;
      else {
        node = node->children[target[idx]];
        idx++;
      }
    }
    return true;
  }
};
  
  
  

abcdef
abcxyz

abc

xyz def




Question: Match string against a list of prefixes.

Input: 1) a list of string prefixes (frozen constant list given at the job startup, O(100)).
       2) many target strings to match, billions of them.
Output: returns true if and only if one prefix in the list matches the target string as a prefix.

Example:
prefixes = ["aa", "bb", "cc"]
target = "aaa" -> returns true
target = "ddd" -> returns false
target = "aa" -> returns true
target = "a" -> returns false

  // Idea 0: to iterate over all the prefixes and compare, O(# prefixes)
  // Idea 1: put all prefix in a hashtable and incrementally append one char from target at a time
  //         and check against the hashtable. Complexity bound by O(max(|prefix|) * (1+load_factor))
  // Idea 2: Trie built from the prefixes. O(max(|prefix|))
 
struct Node {
  // char c;
  struct Node *children[256];
  bool leaf;
}
class Trie {
  // initiated
  Node* root;
  //
  void insert(string s) {
    Node* node = this->root;
    if (node == NULL)
      return;
    else if (s.length() == 0) {
      node->leaf = true;
      return;
    }
    int idx = 0;
    while (idx < s.length()) {
      if (node == NULL) {
        struct Node *tmp = new Node;
        tmp->leaf = false;
        memset(tmp->children, 0, sizeof(tmp->children));
      }
      node->leaf = false;
      node = node->children[target[idx]];
      idx++;
    }
    node->leaf = true;
    
  }
  
  bool prefixMatch (string target) {
    int idx = 0;
    Node* node = this->root;
    if (node == NULL)
      return true;
    while (idx < target.length()) {
      if (leaf)
        return true;
      else if (!leaf && node->childres[target[idx]] == NULL)
        return false;
      else {
        node = node->children[target[idx]];
        idx++;
      }
    }
    return true;
  }
};
  
  
  

abcdef
abcxyz

abc

xyz def



Question: Match string against a list of prefixes.

Input: 1) a list of string prefixes (frozen constant list given at the job startup, O(100)).
       2) many target strings to match, billions of them.
Output: returns true if and only if one prefix in the list matches the target string as a prefix.

Example:
prefixes = ["aa", "bb", "cc"]
target = "aaa" -> returns true
target = "ddd" -> returns false
target = "aa" -> returns true
target = "a" -> returns false

  // Idea 0: to iterate over all the prefixes and compare, O(# prefixes)
  // Idea 1: put all prefix in a hashtable and incrementally append one char from target at a time
  //         and check against the hashtable. Complexity bound by O(max(|prefix|) * (1+load_factor))
  // Idea 2: Trie built from the prefixes. O(max(|prefix|))
 
struct Node {
  // char c;
  struct Node *children[256];
  bool leaf;
}
class Trie {
  // initiated
  Node* root;
  //
  void insert(string s) {
    Node* node = this->root;
    if (node == NULL)
      return;
    else if (s.length() == 0) {
      node->leaf = true;
      return;
    }
    int idx = 0;
    while (idx < s.length()) {
      if (node->children[target[idx]] == NULL) {
        struct Node *tmp = new Node;
        tmp->leaf = false;
        memset(tmp->children, 0, sizeof(tmp->children));
        node->children[target[idx]] = tmp;
      }
      node->leaf = false;
      node = node->children[target[idx]];
      idx++;
    }
    node->leaf = true;
    
  }
  
  bool prefixMatch (string target) {
    int idx = 0;
    Node* node = this->root;
    if (node == NULL)
      return true;
    while (idx < target.length()) {
      if (leaf)
        return true;
      else if (!leaf && node->childres[target[idx]] == NULL)
        return false;
      else {
        node = node->children[target[idx]];
        idx++;
      }
    }
    return true;
  }
};
  
  
  

abcdef
abcxyz

abc

xyz def



Question: Match string against a list of prefixes.

Input: 1) a list of string prefixes (frozen constant list given at the job startup, O(100)).
       2) many target strings to match, billions of them.
Output: returns true if and only if one prefix in the list matches the target string as a prefix.

Example:
prefixes = ["aa", "bb", "cc"]
target = "aaa" -> returns true
target = "ddd" -> returns false
target = "aa" -> returns true
target = "a" -> returns false

  // Idea 0: to iterate over all the prefixes and compare, O(# prefixes)
  // Idea 1: put all prefix in a hashtable and incrementally append one char from target at a time
  //         and check against the hashtable. Complexity bound by O(max(|prefix|) * (1+load_factor))
  // Idea 2: Trie built from the prefixes. O(max(|prefix|))
 
struct Node {
  // char c;
  struct Node *children[256];
  bool leaf;
}
class Trie {
  // initiated
  Node* root;
  //
  Trie() {
    root = new struct Node;
    root->leaf = false;
    memset(root->children, 0, sizeof(root->children));
  }
  
  void insert(string s) {
    Node* node = this->root;
    if (node == NULL)
      return;
    else if (s.length() == 0) {
      node->leaf = true;
      return;
    }
    int idx = 0;
    while (idx < s.length()) {
      if (node->children[target[idx]] == NULL) {
        struct Node *tmp = new Node;
        tmp->leaf = false;
        memset(tmp->children, 0, sizeof(tmp->children));
        node->children[target[idx]] = tmp;
      }
      node->leaf = false;
      node = node->children[target[idx]];
      idx++;
    }
    node->leaf = true;
    
  }
  
  bool prefixMatch (string target) {
    int idx = 0;
    Node* node = this->root;
    if (node == NULL)
      return true;
    while (idx < target.length()) {
      if (leaf)
        return true;
      else if (!leaf && node->childres[target[idx]] == NULL)
        return false;
      else {
        node = node->children[target[idx]];
        idx++;
      }
    }
    return true;
  }
};
  
  
  

abcdef
abcxyz

abc

xyz def
