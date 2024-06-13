/* LC#2

You are given two non-empty linked lists 
representing two non-negative integers. 
The digits are stored in reverse order, 
and each of their nodes contains a single digit. 
Add the two numbers 
and return the sum as a linked list.
 
You may assume the two numbers 
do not contain any leading zero, 
except the number 0 itself.

Constraints:
The number of nodes in each linked list 
is in the range [1, 100].
*/


#include <stdio.h>
#include <iostream>
#include <stack>
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

struct ListNode* push (struct ListNode **head, int val) {
    struct ListNode *node = new ListNode(val);
    node->next = *head;
    return node;
}

// does not work for large numbers
ListNode* addTwoNumbers (ListNode* l1, ListNode* l2) {
    int num1 = 0, num2 = 0;
    int i = 1;
    while (l1 != NULL) {
        num1 += i * l1->val;
        i *= 10;
        l1 = l1->next;
    }
    i = 1;
    while (l2 != NULL) {
        num2 += i * l2->val;
        i *= 10;
        l2 = l2->next;
    }
    num1 += num2;
    ListNode* root = new ListNode(num1 % 10);
    num1 /= 10;
    ListNode* node = root;
    while (num1) {
        ListNode* tmp = new ListNode(num1 % 10);
        num1 /= 10;
        node->next = tmp;
        node = node->next;
    }
    return root;
}

// beats ~64% LC users
ListNode* addTwoNumbersLarge (ListNode* l1, ListNode* l2) {
    int num = 0, carry = 0;
    if (l1) {
        num += l1->val;
        l1 = l1->next;
    }
    if (l2) {
        num += l2->val;
        l2 = l2->next;
    }
    ListNode* root = new ListNode(num % 10);
    carry = num / 10;
    ListNode* node = root;
    while (l1 != NULL || l2 != NULL) {
        num = 0;
        if (l1) {
            num += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            num += l2->val;
            l2 = l2->next;
        }
        num += carry;
        ListNode* tmp = new ListNode(num % 10);
        node->next = tmp;
        node = node->next;
        carry = num / 10;
    }
    if (carry > 0) {
        ListNode* tmp = new ListNode(carry);
        node->next = tmp;
    }
    return root;
}


ListNode* addTwoNumbersOld (ListNode* l1, ListNode* l2) {
    int num1 = 0, num2 = 0;
    while (l1 != NULL) {
        num1 *= 10; num1 += l1->val; l1 = l1->next;
    }
    while (l2 != NULL) {
        num2 *= 10; num2 += l2->val; l2 = l2->next;
    }
    cout << num1 << " " << num2 << endl;
    num1 += num2;
    /*stack<int> st;
    while (num1 != 0) {
        st.push(num1 % 10);
        cout << num1 % 10 << endl;
        num1 /= 10;
    }*/
    struct ListNode *sum = NULL;
    if (num1 == 0) {
        sum = push(&sum, 0);
        return sum;
    }
    else {
        while (num1 != 0) {
            sum = push(&sum, num1 % 10); num1 /= 10;
            // struct ListNode *tmp = new ListNode(st.top());
            // tmp->next = *sum; *sum = *tmp; st.pop();
        }
    }
    /*while (!st.empty()) {
        sum = push(&sum, st.top()); st.pop();
        // struct ListNode *tmp = new ListNode(st.top());
        // tmp->next = *sum; *sum = *tmp; st.pop();
    }*/
    return sum;
}

//ListNode* addTwoNumbersReverse (ListNode* l1, ListNode* l2) {
    
//}

ListNode* mergeTwoLists (ListNode* l1, ListNode* l2) {
    ListNode dummy(-1); //ListNode* dummy = new ListNode(-1);
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
            (tail->next) = l2;
            l2 = l2->next;
        }
        else {
            (tail->next) = l1;
            l1 = l1->next;
        }
        tail = tail->next;
    }
    return dummy.next;
}

// O(m * n)
int intersectionNode (ListNode* l1, ListNode* l2) {
    while (l2) {
        ListNode* tmp = l1;
        while (tmp) {
            if (tmp->val == l2->val)
                return l2->val;
            tmp = tmp->next;
        }
        l2 = l2->next;
    }
    return -1;
}

void printList (ListNode *head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    struct ListNode *l1 = new ListNode(5);
    l1->next = new ListNode(6);
    l1->next->next = new ListNode(4);
    l1->next->next->next = NULL;

    struct ListNode *l2 = new ListNode(2);
    l2->next = new ListNode(4);
    l2->next->next = new ListNode(3);
    l2->next->next->next = NULL;
    // num1 = 564 and num2 = 243
    struct ListNode *head = addTwoNumbers(l1, l2);
    printList (head);
    
    struct ListNode *l3 = new ListNode(7);
    l3->next = new ListNode(2);
    l3->next->next = new ListNode(4);
    l3->next->next->next = new ListNode(3);
    l3->next->next->next->next = NULL;
    // num3 = 7243 and num2 = 243
    struct ListNode *head2 = addTwoNumbers(l3, l2);
    printList (head2);
    
    struct ListNode *l4 = new ListNode(7);
    l4->next = new ListNode(2);
    l4->next->next = new ListNode(4);
    l4->next->next->next = new ListNode(3);
    l4->next->next->next->next = new ListNode(8);
    l4->next->next->next->next->next = NULL;
    
    struct ListNode *l5 = new ListNode(5);
    l5->next = new ListNode(6);
    l5->next->next = new ListNode(3);
    l5->next->next->next = new ListNode(8);
    l5->next->next->next->next = NULL;
    // struct ListNode *head3 = mergeTwoLists(l4, l5);
    printList(l4); printList(l5);
    // printList (head3);
    cout << intersectionNode(l4, l5) << endl;
    return 0;
}
