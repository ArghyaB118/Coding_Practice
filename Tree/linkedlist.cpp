//#include <bits/stdc++.h>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() {
		this->val = 0;
		this->next = NULL;
	}
	ListNode(int x) : val(x), next(NULL) {}
};


void insert(int new_val) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->val = new_val;
    new_node->next = head;
    head = new_node;
}

void display() {
    struct Node* ptr;
    ptr = head;
    while (ptr != NULL) {
        cout << ptr-> val << " ";
        ptr = ptr->next;
    }
    cout << "\n";
}


struct ListNode* push(struct ListNode **head, int val) {
	struct ListNode *node = new ListNode(val);
	node->next = *head;
	return node;
}

void push2(struct ListNode **head, int val) {
	/* allocate node */
	struct ListNode *node = new ListNode();
	/* put in the data */
	node->val = val;
	/* link the old list off the new node */
	node->next = *head;
	/* move the head to point to the new node */
	*head = node;
}

void printList(ListNode *head) {
	while (head != NULL) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

// How to delete a node from a list
void deleteNode(ListNode* node) {
    while (node->next != NULL) {
        node->val = node->next->val;
        if (node->next->next != NULL)
            node = node->next;
        else
            node->next = NULL;
    }
}

// Reverse a linked list
ListNode* reverseList (ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;
    ListNode* listnode = head->next;
    ListNode* reverselistnode = head;
    reverselistnode->next = NULL;
    while (listnode != NULL) {
        ListNode* temp = listnode;
        listnode = listnode->next;
        temp->next = reverselistnode;
        reverselistnode = temp;
    }
    return reverselistnode;
}


bool hasCycle (ListNode *head) {
    unordered_set<ListNode*> s;
    while(head != NULL) {
        if (s.find(head) != s.end())
            return true;
        s.insert(head);
        head = head->next;
    }
}
    
bool hasCycle2 (ListNode *head) {
    ListNode *slow_p = head, *fast_p = head;
    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p)
            return true;
    }
    return false;
}

/*
You are given a singly-linked list that contains N integers. 
A subpart of the list is a contiguous set of even elements, 
bordered either by either end of the list or an odd element. 
For example, if the list is [1, 2, 8, 9, 12, 16], 
the subparts of the list are [2, 8] and [12, 16].

Then, for each subpart, the order of the elements is reversed. 
In the example, this would result in the new list, [1, 8, 2, 9, 16, 12].
The goal of this question is: given a resulting list, 
determine the original order of the elements.
*/

void appendNode (ListNode *head, int val) {
	while (head->next != NULL) 
		head = head->next;
	struct ListNode *node = new ListNode(val);
	head->next = node;
	node->next = NULL;
}

struct ListNode* reverse (ListNode* Node) {
	struct ListNode *head = new ListNode(Node->val);
	Node = Node->next;
	stack<int> st;
	while (Node != NULL) {
		if (Node->val % 2 != 0) {
			if (st.empty())
				appendNode(head, Node->val);
			else {
				while (!st.empty()) {
					appendNode(head, st.top());
					st.pop();
				}
				appendNode(head, Node->val); // printList(head);
			}
		}
		else
			st.push(Node->val);
		Node = Node->next;
	}
	while (!st.empty()) {
		appendNode(head, st.top());
		st.pop();
	}
	return head;
}

struct ListNode *arrayToList(int arr[], int size) {
	ListNode *root = NULL;
	for (int i = size - 1; i >= 0; i--) {
		push2(&root, arr[i]);
	}
	return root;
}


/*
How to count duplicates in a linked list
*/

int countDuplicate(ListNode* head) {
	int count = 0;
	while (head->next != NULL) {
		ListNode *ptr = head->next;
		while (ptr != NULL) {
			if (head->val == ptr->val) {
				count++;
			}	
			ptr = ptr->next;
		}
		head = head->next;
	}
	return count;
}

int countDuplicateHash(ListNode* head) {
	if (head == NULL)
		return 0;
	int count = 0;
	vector<int> elts;
	while (head != NULL) {
		vector<int>::iterator it = find(elts.begin(), elts.end(), head->val);
		if (it != elts.end())
			count++;
		elts.insert(elts.begin(), head->val);
		head = head->next;
	}
	return count;
}

/* LC#21
 
How to merge two sorted linked list
https://www.geeksforgeeks.org/merge-two-sorted-linked-lists/
You are given the heads 
of two sorted linked lists list1 and list2.

Merge the two lists in a one sorted list. 
The list should be made 
by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Input: list1 = [], list2 = []
Output: []

Input: list1 = [], list2 = [0]
Output: [0]
*/

ListNode* mergeTwoSortedLists (ListNode* l1, ListNode* l2) {
	ListNode dummy(-1);
	ListNode* tail = &dummy;
	dummy.next = NULL;
	while(1) {
		if (l1 == NULL) {
			tail->next = l2;
			break;
		}
		else if (l2 == NULL) {
			tail->next = l1;
			break;
		}
		if (l1->val > l2->val) {
			tail->next = l2;
			l2 = l2->next;
		}
		else {
			tail->next = l1;
			l1 = l1->next;
		}
		tail = tail->next;
	}
	return dummy.next;
}

/* LC#23
 
You are given an array of k linked-lists lists, 
each linked-list is sorted in ascending order.

Merge all the linked-lists into 
one sorted linked-list and return it.

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
1->4->5,
1->3->4,
2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6

Input: lists = []
Output: []

Input: lists = [[]]
Output: []
*/

// beats ~6% LC users
ListNode* mergeKLists(vector<ListNode*>& lists) {
	if (lists.size() == 0)
        return NULL;
    int n = lists.size();
    ListNode* dummy = new ListNode(-1, NULL);
    ListNode* head = dummy;
    while (true) {
    	int i = -1;
    	for (int j = 0; j < n; j++) {
    		if (lists[j] && i == -1)
    			i = j;
    		else if (lists[j] && i >= 0 && lists[j]->val < lists[i]->val)
    			i = j;
    	}
    	if (i == -1)
    		return dummy->next;
    	else {
    		// ListNode* node = new ListNode(lists[i]->val, NULL);
    		head->next = lists[i]; // node;
    		head = head->next;
    		lists[i] = lists[i]->next;
    	}
    }
    return dummy->next;
}

// beats ~25% LC users
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.size() == 0)
        return NULL;
    ListNode dummy(-1);
    ListNode* tail = &dummy;
    dummy.next = NULL;
    while (1) {
        int count = 0;
        for (int i = 0; i < lists.size(); i++)
            if (lists[i] != NULL)
                count++;
        if (count == 0) {
            cout << "here" << endl;
            return dummy.next;
        }
        else if (count == 1) {
            for (int i = 0; i < lists.size(); i++) {
                if (lists[i] != NULL) {
                    tail->next = lists[i];
                    return dummy.next;
                }
            }
        }
        else {
            // break;
            int tmp = 10000;
            for (int i = 0; i < lists.size(); i++) {
                if (lists[i] != NULL)
                    tmp = min(tmp, lists[i]->val);
            }
            for (int i = 0; i < lists.size(); i++) {
                if (lists[i] != NULL) {
                    if (lists[i]->val == tmp) {
                        tail->next = lists[i];
                        lists[i] = lists[i]->next;
                        tail = tail->next;
                    }
                }
            }
        }
    }
    return dummy.next;
}


/* LC#203

Given the head of a linked list 
and an integer val, 
remove all the nodes of the linked list 
that has Node.val == val, 
and return the new head.
*/

// beats ~88% LC users
ListNode* removeElements(ListNode* head, int val) {
    if (!head)
		return head;
	while (head && head->val == val)
		head = head->next;
	if (!head)
		return head;
	ListNode* node = head;
	while (node->next) {
		if (node->next->val != val)
			node = node->next;
		else
			node->next = node->next->next;
	}
	return head;
}


// https://www.geeksforgeeks.org/reverse-a-linked-list/
ListNode* reverseList(ListNode* head) {
	ListNode* current = head; 
	ListNode *prev = NULL, *next = NULL;
	while (current != NULL) {
		next = current->next;// cout << next->val;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
	return head;
}

void swapNode(int x, int y) {
    if (x == y) return;
    // Search for x (keep track of prevX and CurrX)
    Node *prevX = NULL, *currX = head;
    while (currX && currX->val != x) {
        prevX = currX;
        currX = currX->next;
    }
    // Search for y (keep track of prevY and CurrY)
    Node *prevY = NULL, *currY = head;
    while (currY && currY->val != y) {
        prevY = currY;
        currY = currY->next;
    }
    if (currX == NULL || currY == NULL) return;
    // If x is not head of linked list
    if (prevX != NULL)
        prevX->next = currY;
    else // Else make y as new head
        head = currY;
    // If y is not head of linked list
    if (prevY != NULL)
        prevY->next = currX;
    else // Else make x as new head
        head = currX;
    // Swap next pointers
    Node *temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

/* LC#19

Given the head of a linked list, 
remove the nth node 
from the end of the list 
and return its head.

Constraints:
The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
 
Follow up: Could you do this in one pass?
*/

// beats ~70% LC users
ListNode* removeNthFromEnd(ListNode* head, int n) {
	if (!head)
		return NULL;
	vector<ListNode*> nodes;
	while (head) {
		nodes.push_back(head);
		head = head->next;
	}
	int count = nodes.size();
	int remove = (count - 1) - (n - 1);
	if (remove == 0 && count == 1)
		return NULL;
	else if (remove == 0 && count > 1)
		return nodes[1];
	else if (remove == count - 1) {
		nodes[count - 2]->next = NULL;
		return nodes[0];
	}
	
	nodes[remove - 1]->next = nodes[remove + 1];
	return nodes[0];
}

/* LC#92

Given the head of a singly linked list 
and two integers left and right 
where left <= right, 
reverse the nodes of the list 
from position left to position right, 
and return the reversed list.
*/

// beats ~100% LC users
ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (left == right)
		return head;

	ListNode* dummy = new ListNode(0, head);

	ListNode* leftnode = dummy;
	if (left > 1) {
		for (int i = 0; i < left - 1; i++) {
			leftnode = leftnode->next;
		}
	}
	
	ListNode* tmp = leftnode->next;
	stack<ListNode*> st;
	for (int i = 0; i < right - left + 1; i++) {
		st.push(tmp);
		tmp = tmp->next;
	}

	ListNode* rightnode = tmp;
	tmp = leftnode;

	while (!st.empty()) {
		tmp->next = st.top();
		tmp = st.top();
		st.pop();
	}
	tmp->next = rightnode;

	return dummy->next;
}

int main() {
	struct ListNode *head = new ListNode(1);
	head = push(&head, 2);
	head = push(&head, 3);
	push2(&head, 4);
	printList(head); deleteNode(head); printList(head);

	int arr[] = {1, 8, 2, 9, 16, 12};
	int size = sizeof(arr) / sizeof(arr[0]);
	struct ListNode *head2 = arrayToList(arr, size);
	printList(head2); head2 = reverse(head2); printList(head2);

	int arr2[] = {1, 2, 2, 3, 4, 4, 5, 6};
	int size2 = sizeof(arr2) / sizeof(arr2[0]);
	struct ListNode *head3 = arrayToList(arr2, size2);
	cout << countDuplicate(head3) << endl;
	cout << countDuplicateHash(head3) << endl;
    
    ListNode* l1 = NULL; l1->val = 5; l1->next->val = 6; l1->next->next->val = 4;
    ListNode* l2 = NULL; l2->val = 2; l2->next->val = 4; l2->next->next->val = 3;
	return 0;
}
