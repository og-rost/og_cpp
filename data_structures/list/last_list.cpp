#include <iostream>
#include <exception>
#include <stdexcept>

class list {
	struct node;
	struct data_node;
	node* dummy;	
public:
	struct iterator;
	//friend struct iterator;
	list(); 								/* ++ */
	list(const list&);
	list& operator=(const list&);
	~list() { /*clear(); */}				/* ++ */
	iterator insert(iterator, const int&);  /* ++ */
	iterator erase(iterator); 				/* ++ */
	void push_front(const int&);			/* ++ */
	void pop_front();						/* ++ */
	void push_back(const int&);				/* ++ */
	void pop_back();						/* ++ */
	void clear();
	size_t size();							/* ++ */
	bool empty();
	iterator begin(); 						/* ++ */
	iterator end();	 						/* ++ */
};

struct list::node {
	node* next;
	node* prev;
	node() : next(nullptr), prev(nullptr) {}
};

struct list::data_node : public list::node {
	int data;
	data_node(int d) : data(d) {}
};

struct list::iterator {
	node* curr;
	iterator(node* p) : curr(p) {}

	iterator& operator++();
	iterator  operator++(int);
	iterator& operator--();
	iterator  operator--(int);
	int&      operator*();
	int*      operator->();
	friend    bool operator==(iterator, iterator);
	friend    bool operator!=(iterator, iterator);
};

typename list::iterator& list::iterator::operator++() {
	if (curr && curr->next) {
		curr = curr->next;
		return *this;
	}
	throw std::exception();
}

typename list::iterator list::iterator::operator++(int) {
	if (curr && curr->next) {
		iterator temp = *this;
		curr = curr->next;
		return temp;
	}
	throw std::exception();
}

typename list::iterator& list::iterator::operator--() {
	if (curr && curr->prev) {
		curr = curr->prev;
		return *this;
	}
	throw std::exception();
}

typename list::iterator list::iterator::operator--(int) {
	if (curr && curr->prev) {
		iterator temp = *this;
		curr = curr->prev;
		return temp;
	}
	throw std::exception();
}

int& list::iterator::operator*() {
	if(curr /*&& curr != dummy*/)
		return static_cast<data_node*>(curr)->data;
	throw std::exception();
}

int* list::iterator::operator->() {
	if(curr /*&& curr != dummy*/)
		return &(static_cast<data_node*>(curr)->data);
	throw std::exception();
}

bool operator==(typename list::iterator lhs, typename list::iterator rhs) {
	return lhs.curr == rhs.curr;
}

bool operator!=(typename list::iterator lhs, typename list::iterator rhs) {
	return lhs.curr != rhs.curr;
}

typename list::iterator list::begin()  {
	if(dummy->next)
		return iterator(dummy->next);
	return iterator(dummy);
}

typename list::iterator list::end()  {
	return iterator(dummy);
}

list::list() {
	dummy = new node;
}

typename list::iterator list::insert(iterator it, const int& val) {
	node* p = new data_node(val);

	if(!it.curr->next) {
		it.curr->next = p;
		it.curr->prev = p;
		p->next = dummy;
		p->prev = dummy;
	}

	else {	
		p->next = it.curr;
		p->prev = it.curr->prev;
		if(it.curr->prev)
			it.curr->prev->next = p;
		it.curr->prev = p;
	}
	return iterator(p);
}

typename list::iterator list::erase(iterator it) {
	if(it.curr == dummy)
		return iterator(dummy);
	if(it.curr->prev)
		it.curr->prev->next = it.curr->next;
	if(it.curr->next)
		it.curr->next->prev = it.curr->prev;
	iterator temp = iterator(it.curr->prev);
	delete it.curr;
	return temp;
}

void list::push_front(const int& val) {
	this->insert(this->begin(), val);
}

void list::push_back(const int& val) {
	this->insert(this->end(), val);
}

void list::pop_front() {
	this->erase(this->begin());
}

void list::pop_back() {
	this->erase(--(this->end()));
}

void list::clear() {
	node* p = this->begin().curr;
	while(p->next != dummy) {
		node* temp = p->next;
		delete p;
		p = temp;
	}
}

size_t list::size() {
	node* p = this->begin().curr;
	size_t sz = 0;
	while(p != dummy) {
		++sz;
		p = p->next;
	}
	return sz;
}

bool list::empty() {
	return this->begin() == this->end();
}

int main() {
	list lst;
	lst.push_back(42);
	lst.push_back(52);
	lst.push_front(32);

	lst.clear();
	//for(list::iterator it = lst.begin(); it != lst.end(); ++it)
		//std::cout<<*it<<"  ";

	std::cout<<lst.size()<<std::endl;
}