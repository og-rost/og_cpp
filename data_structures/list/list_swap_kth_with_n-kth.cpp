#include <iostream>
using std::cout;
using std::endl; 

struct node {
    int data;
    node* next;
    node(int val) : data(val) {}
};

void push(node* &head, int val) {
    node* p = new node(val);    
    p->next = head;
    head = p;
}
 
void printList(node* ptr) {
    while (ptr) {
        cout << ptr->data <<" ";
        ptr = ptr->next;
    }
    cout << endl;
}
 
int countNodes(node* ptr) {
    int count = 0;
    while (ptr) {
        ++count;
        ptr = ptr->next;
    }
    return count;
}
 
void swapKth(node* head, int k) {
    if (countNodes(head) < k) return;     
    node* curr = head;
    while(--k)
        curr = curr -> next;      
    node* x = curr;
    node* y = head;
    while(curr->next) {
        curr = curr -> next;
        y = y -> next; 
    }    
    std::swap(y->data, x->data);
}
 
int main() {    
    node* head = nullptr;
    for (int i = 8; i >= 1; i--)
       push(head, i);   
    printList(head);
    swapKth(head, 4);
    printList(head);
    return 0;
}