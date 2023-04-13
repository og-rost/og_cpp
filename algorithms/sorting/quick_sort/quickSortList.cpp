#include <iostream>

struct node {
    int data;
    node* next;
    node(int val) : data(val), next(nullptr) {}
}; 

node* getTail(node* curr) {
    while (curr && curr->next)
        curr = curr->next;
    return curr;
}

// Partitions the list taking the last element as the pivot
node* partition(node* head, node* end, node*& newHead, node*& newEnd) {
    node* pivot = end;
    node* prev = nullptr;
    node* cur = head;
    node* tail = pivot;

    //changes to head and end are updated in the newHead and newEnd 
    while (cur != pivot) {
        if (cur->data < pivot->data) {
            // First node  less than the pivot becomes the new head
            if (!newHead)
                newHead = cur; 
            prev = cur;  
            cur = cur->next;
        }
        else {
            // Move cur node to next of tail, and change tail
            if (prev)
                prev->next = cur->next;
            node* tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }     
    if (!newHead)
        newHead = pivot;    
    newEnd = tail;
    return pivot;
}

node* sort(node* head, node* end) {    
    if (!head || head == end)
        return head; 
    node* newHead = nullptr;
    node* newEnd  = nullptr;
    node* pivot = partition(head, end, newHead, newEnd);    
    if (newHead != pivot) {
        // Set the node before the pivot node as NULL
        node* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = nullptr;   
        newHead = sort(newHead, tmp); 
        // Change next of last node of the left half to pivot
        tmp = getTail(newHead);
        tmp->next =  pivot;
    }    
    pivot->next = sort(pivot->next, newEnd); 
    return newHead;
}

void quickSort(node*& head) {
    head = sort(head, getTail(head));    
}

void printList(node* ptr) {
    while (ptr) {
        std::cout << ptr->data << "   ";
        ptr = ptr->next;
    }
    std::cout<<std::endl;    
}

void push(node*& head, int val) {    
    node* p = new node(val);
    p->next = head;  
    head = p;
}

int main() {
    node* list = nullptr;
    push(list, 5);
    push(list, 20);
    push(list, 4);
    push(list, 3);
    push(list, 30); 
    std::cout << "Linked List before sorting "<<std::endl;
    printList(list); 
    quickSort(list); 
    std::cout << "Linked List after sorting "<<std::endl;
    printList(list); 
    return 0;
}
