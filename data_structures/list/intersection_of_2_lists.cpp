#include <iostream>
using std::cout;
using std::endl;
 
struct node {
    int data;
    node* next;
    node(int val) : data(val) {}
};
 
int getCount(node* head) {
    int count = 0;
    while (head) {
        ++count;
        head = head->next;
    }
    return count;
}
 
void printList(node* ptr) {
    while (ptr) {
        cout << ptr->data <<" ";
        ptr = ptr->next;
    }
    cout << endl;
}

node* getHelper(node* h1, node* h2, int dist) {
    node* c1 = h1;
    node* c2 = h2;
  
    for(int i = 0; i < dist; ++i) {
        if(!c1) return nullptr;
        c1 = c1->next;
    }
 
    while(c1 && c2) {
        if(c1 == c2)
            return c1;
        c1= c1->next;
        c2= c2->next;
    }
    return nullptr;
}

node* getInter(node* h1, node* h2) {
    int c1 = getCount(h1);
    int c2 = getCount(h2);
    if(c1 > c2)
        return getHelper(h1, h2, c1 - c2);
    else 
        return getHelper(h2, h1, c2 - c1);
} 

int main() {
    node* newNode;    
    node* head2 = new node(2);     
    newNode = new node(3);
    head2->next = newNode; 
    newNode = new node(4);   
    head2->next->next = newNode;

    node* head1 = new node(1);  
    newNode = new node(5);    
    head1->next = newNode;
    head2->next->next->next  = newNode; 
    newNode = new node(6); 
    head1->next->next= newNode; 
    head1->next->next->next = NULL;

    printList(head1);
    printList(head2);
 
    cout<<getInter(head1, head2)->data<<endl;
    return 0;  
}