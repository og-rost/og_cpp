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

node* copy(node* head) {	
	if (!head)
		return nullptr;	
	std::unordered_set<node*> hash;
	
	node* new_head = new node(head->data);
	hash.emplace(head);
	if (head->prev) {
		new_head->prev = new node(head->prev->data);
		hash.emplace(head->prev);			
	}		
	head = head->next;
	node* temp = new_head;
	
	for (node* i = head; i != nullptr; i = i -> next) {
		std::unordered_set<node*>::iterator iter = hash.find(i);
		if (iter == hash.end()) {
			temp->next = new node(i->data);
			hash.emplace(i);
			temp = temp->next;
		}
		else {
			temp->next = *iter;
			temp = temp->next;			
		}
		
		iter = hash.find(i->prev);
		if (iter == hash.end()) {
			if (i->prev) {
				temp->prev = new node(i->prev->data);
				hash.emplace(i->prev);
			}
			else temp->prev = nullptr;			
		}
		else temp->prev = *iter;			
	}
	
	return new_head;
}

int main() {
	srand(time(0));
	node* head = create();
	print(head);
	print_prev(head);

	node* new_head = copy(head);
	
	print(new_head);
	print_prev(new_head);
	
	return 0;
}