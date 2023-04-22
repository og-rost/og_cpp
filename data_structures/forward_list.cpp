#include <iostream>

class forward_list {
private:
	class node;
	node* root;
	void copy(node*);
	void clear(node*);
public:
	forward_list() : root(nullptr) {}
	forward_list(const forward_list&);
	forward_list(forward_list&&);
	forward_list& operator= (const forward_list&);
	forward_list& operator= (forward_list&&);
	bool empty() const;
	void clear();
	void push_front(const int&);
	void pop_front();
	class iterator;
	void insert_after(iterator, const int&);
	void erase_after(iterator);
	void quick_sort();
	void merge_sort();
	void print() const;	
	iterator begin();
	iterator end();
};

class forward_list::node {
public:
	int data;
	node* next;
	node(int d) : data(d), next(nullptr) {}
};

class forward_list::iterator {	
public:
	node* curr;
	iterator(node* ptr = nullptr) : curr(ptr) {}
	iterator(const iterator& rhs) : curr(rhs.curr) {}	
	iterator& operator= (const iterator&);
	iterator& operator++ ();
	iterator operator++ (int);
	int& operator*();
	friend bool operator== (iterator, iterator);
	friend bool operator!= (iterator, iterator);
};

forward_list::iterator& forward_list::iterator::operator= (const iterator& rhs) {
	curr = rhs.curr;
	return *this;
}

forward_list::iterator& forward_list::iterator::operator++ () {
	if (curr)
		curr = curr->next;
	return *this;
}

forward_list::iterator forward_list::iterator::operator++ (int) {
	iterator temp = *this;
	++*this;
	return temp;
}

int& forward_list::iterator::operator*() {
	return curr->data;
}

bool operator== (forward_list::iterator lhs, 
				 forward_list::iterator rhs) {
	if (lhs.curr == rhs.curr)
		return true;
	return false;
}

bool operator!= (forward_list::iterator lhs,
				forward_list::iterator rhs) {
	if (lhs == rhs)
		return false;
	return true;
}

void forward_list::copy(node* rhs) {
	if (rhs) {
		root = new node(rhs->data);		
	}
	else return;
	node* temp = root;
	while (rhs->next) {
		temp->next = new node(rhs->next->data);
		temp = temp->next;
		rhs = rhs->next;
	}
}

forward_list::forward_list(const forward_list& rhs) {
	copy(rhs.root);
}

forward_list::forward_list(forward_list&& temp) : root(temp.root) {
	temp.root = nullptr;
}

forward_list& forward_list::operator= (const forward_list& rhs) {
	if (root) clear();
	copy(rhs.root);
	return *this;
}

forward_list& forward_list::operator= (forward_list&& temp) {
	if (root) clear();
	root = temp.root;
	temp.root = nullptr;
	return *this;
}

void forward_list::clear(node* rt) {
	if (rt) {
		clear(rt->next);
		delete rt;
	}
}

void forward_list::clear() {
	clear(root);
	root = nullptr;
}

bool forward_list::empty() const {
	return (root == nullptr) ? true : false;
}

void forward_list::push_front(const int& data) {
	node* p = new node(data);
	p->next = root;
	root = p;
}

void forward_list::pop_front() {
	if (root) {
		node* temp = root->next;
		delete root;
		root = temp;
	}
}

void forward_list::insert_after(iterator ptr, const int& data) {
	if (ptr.curr) {
		node* p = new node(data);
		p->next = ptr.curr->next;
		ptr.curr->next = p;
	}
}

void forward_list::erase_after(iterator ptr) {
	if (ptr.curr && ptr.curr->next) {
		node* temp = ptr.curr->next;
		ptr.curr->next = ptr.curr->next->next;
		delete temp;
	}
}

forward_list::iterator forward_list::begin() {
	return iterator(root);
}

forward_list::iterator forward_list::end() {
	return nullptr;
}

void forward_list::print() const {
	node* temp = root;
	while (temp) {
		std::cout << temp->data << "  ";
		temp = temp->next;
	}
	std::cout << std::endl;	
}

int main() {
	forward_list list;
	
	//std::cout << list.empty() << std::endl;
	list.push_front(90);
	list.push_front(80);
	list.push_front(70);
	list.push_front(60);
	list.push_front(50);
	list.push_front(40);
	list.push_front(30);
	list.push_front(20);
	list.push_front(10);
	
	list.print();
	//list.clear();
	list.pop_front();
	list.print();
	forward_list::iterator iter = list.begin();
	++iter; ++iter; ++iter;
	list.erase_after(iter);
	list.print();
	list.insert_after(++iter, 100);
	list.print();
	std::cout << list.empty() << std::endl;
	for (iter = list.begin(); iter != list.end(); ++iter) {
		std::cout << *iter << "  ";
	}
	std::cout << std::endl;
	

	forward_list lll = list;
	lll.print();
	list.clear();
	lll.print();
	
	forward_list  ls;
	ls = lll;
	ls.print();
}