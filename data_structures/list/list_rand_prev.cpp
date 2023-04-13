#include <iostream>
#include <vector>
#include <unordered_set>
#include <ctime>
#include <cstdlib>
#include <algorithm>

struct node {
	int data;
	node* prev;
	node* next;
	node(int d) : data(d), next(nullptr), prev(nullptr) {}
};

node* create() {
	node* head = new node(rand() % 60 + 10);
	node* temp = head;
	std::vector<node*> vec;
	vec.push_back(head);
	vec.push_back(nullptr);
	for (int i = 0; i < 10; ++i) {
		node* p = new node(rand() % 60 + 10);
		vec.push_back(p);
		temp->next = p;
		temp = p;
	}
	vec.pop_back();	

	std::random_shuffle(vec.begin(), vec.end());
	int i = 0;
	node* iter = head;
	while (iter) {
		iter -> prev = vec[i++];
		iter = iter -> next;
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

void print_prev(node* head) {
	while (head) {
		if (head->prev)
			std::cout << head->prev->data << " ";
		else
			std::cout << "99" << " ";
		head = head->next;
	}
	std::cout << std::endl << std::endl;
}

void insert(node* p) {
	node* temp = new node(p->data);
	temp->next = p->next;
	p->next = temp;
}

node* copy(node* head) {	
	if (!head) return nullptr;

	node* temp = nullptr;
	node* iter = head;
	while (iter) {
		insert(iter);
		if (!temp) temp = iter;		
		iter = iter->next->next;
	}
	
	iter = head;
	while (iter) {
		iter->next->prev = iter->prev;
		iter->next = iter->next->next;
		iter = iter->next;
	}
	
	return temp;
}

void clear(node* p) {
	while(p) {
		node* temp = p->next;
		delete p;
		p = temp;
	}
}

int main() {
	srand(time(0));
	node* head = create();
	print(head);
	print_prev(head);

	node* new_head = copy(head);
	clear(head);
	print(new_head);
	print_prev(new_head);
	
	return 0;
}