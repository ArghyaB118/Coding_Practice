/*
Merge two sorted linked list
*/

SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    if (!head1 && !head2)
        return NULL;
    else if (!head1)
        return head2;
    else if (!head2)
        return head1;
    SinglyLinkedListNode* dummy;
    if (head1->data <= head2->data) {
        dummy = head1;
        head1 = head1->next;
    }
    else {
        dummy = head2;
        head2 = head2->next;
    }
    SinglyLinkedListNode* head = dummy;
    while (head1 && head2) {
        if (head1->data <= head2->data) {
            head->next = head1;
            head1 = head1->next;        
        }
        else if (head1->data > head2->data) {
            head->next =  head2;
            head2 = head2->next;        
        }  
        head = head->next;              
    }
    if (head1) {
        head->next = head1;
    }
    if (head2) {
        head->next = head2;
    }
    return dummy;
}