class iterator {
	node* ptr;
public:
	iterator() = default;		
	iterator(const iterator& rhs) : ptr(rhs.ptr) {}
	~iterator() = default;	
	iterator& operator=(const iterator& rhs) {		
		if (this != &rhs) {
			ptr = rhs.ptr;
		}
		return *this;
	}
	iterator& operator++()	{			
		ptr = ptr->next;
		return *this;
	}
		
	iterator operator++(int) {	
		iterator tmp = *this;
		++*this;
		return tmp;
	}	
		
	iterator& operator--()	{	
		ptr = ptr->prev;
		return *this;
	}	

	iterator operator--(int) {
		iterator tmp = *this;
		--*this;
		return tmp;
	}
		
	T& operator*() {
		if (ptr)
	    	return ptr->data;		
	}

	T* operator->() {
		return ptr;
	}


	friend bool operator == (const iterator&, const iterator&);
	friend bool operator != (const iterator&, const iterator&);		
};

bool operator == (const iterator& a, const iterator& b) {
	return (a.ptr == b.ptr);
}

bool operator != (const iterator& a, const iterator& b) {
	return   !(a.ptr == b.ptr);
}