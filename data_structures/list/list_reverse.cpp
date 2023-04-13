#include <iostream>

struct node {
	int data;
	node* prev;
	node* next;
	node(int d) : data(d), next(nullptr), prev(nullptr) {}
};

node* create() {
	node* temp = new node(rand() % 60 + 10);
	node* head = temp;
	for (int i = 0; i < 10; ++i) {
		temp->next = new node(rand() % 60 + 10);
		temp = temp->next;
	}
	return head;	
}

void print(node* head) {
	while (head) {
		std::cout << head -> data << " ";
		head = head -> next;
	}
	std::cout << std::endl;
}

void reverse(node*& head) {
	node* prev = nullptr;
	node* curr = head;
	node* next;
	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
}


int main() {
	node* head = create();
	print(head);
	reverse(head);	
	print(head);	
	return 0;
}