#pragma once

template <class T>
class node;

template <class T>
class dummy_node {
public:
	dummy_node *next;
	dummy_node() : next(nullptr) {}
	dummy_node(dummy_node *n) : next(n) {}
};

template <class T>
class node : public dummy_node<T> {
public:
	T data;
	node(const T &d)
		: dummy_node(nullptr), data(d)
	{
	}
};

template <class T>
class list {
	typedef size_t		size_type;
	typedef T			value_type;
	typedef T*			pointer;
	typedef T&			reference;

	dummy_node<T> *head, *tail, *last;
	
public:
	list() 
		: head(nullptr), tail(new dummy_node<T>), last(nullptr)
	{
	}


	list(const list &ob) : tail(new dummy_node<T>) {
		dummy_node<T> *tmp = ob.head;
		while (tmp != nullptr) {
			push_back(tmp->data);
			tmp = tmp->next;
		}
	}

	list& operator=(list rhs) {
		clean();
		head = rhs.head;
		tail = rhs.tail;
		rhs.head = rhs.tail = nullptr;
	}

	T& front() {
		return static_cast<node<T> *>(head)->data;
	}

	T& back() {
		return static_cast<node<T> *>(last)->data;
	}
	void push_back(const value_type &val) {
		if (head == nullptr) {
			head = new node<T>(val);		
			head->next = tail;
			last = head;
		}
		else {
			last->next = new node<T>(val);
			last->next->next = tail;
			last = last->next;

		}
	}

	void push_front(const value_type &val) {
		if (head == nullptr) {
			push_back(val);
		}
		else {
			dummy_node<T> *tmp = new node<T>(val);
			tmp->next = head;
			head = tmp;
		}
	}


	void pop_front() {
		if (head == nullptr) {
			return;
		}
		dummy_node<T> *tmp = head;
		head = head->next;
		delete tmp;		 
	}
	
	~list() {
		clean();
	}

	void clean() {

		while (head != nullptr) {
			tail = head->next;
			delete head;
			head = tail;
		}
		last = head = tail = nullptr;
}
	class iterator {
		dummy_node<T> *curr;
	public:
		iterator() : curr(nullptr) {}

		iterator(dummy_node<T> *n) : curr(n) {}

		T& operator*() {
			return static_cast<node<T> *>(curr)->data;
		}

		iterator& operator++() {
			curr = curr->next;
			return *this;
		}

		bool operator==(const iterator &rhs) {
			return curr == rhs.curr;
		}

		bool operator!=(const iterator &rhs) {
			return !operator==(rhs);
		}

		T* operator->() {
			return &operator*(curr);
		}


		iterator operator++(int) {
			node<T> *tmp = curr;
			curr = curr->next;
			return tmp;
		}

	};

	typedef const iterator const_iterator;

	iterator begin() {
		return head;
	}

	iterator begin() const {
		return head;
	}

	iterator end() {
		return tail;
	}

	iterator end() const {
		return tail;
	}
};