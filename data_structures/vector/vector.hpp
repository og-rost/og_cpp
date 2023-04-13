#include <memory>
#include <stdexcept>
#include <iterator>

template  <typename T>
class vector {
public:
	class iterator : public std::iterator<std::random_access_iterator_tag, T> {
	public:
	    using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
	    iterator() : _ptr(nullptr) {}
	    iterator(T* rhs) : _ptr(rhs) {}
	    iterator(const iterator &rhs) : _ptr(rhs._ptr) {}
	    inline iterator& operator+=(difference_type rhs) {_ptr += rhs; return *this;}
	    inline iterator& operator-=(difference_type rhs) {_ptr -= rhs; return *this;}
	    inline T& operator*() const {return *_ptr;}
	    inline T* operator->() const {return _ptr;}
	    inline T& operator[](difference_type rhs) const {return _ptr[rhs];}

	    inline iterator& operator++() {++_ptr; return *this;}
	    inline iterator& operator--() {--_ptr; return *this;}
	    inline iterator operator++(int) const {iterator tmp(*this); ++_ptr; return tmp;}
	    inline iterator operator--(int) const {iterator tmp(*this); --_ptr; return tmp;}
	    inline difference_type operator-(const iterator& rhs) const {return iterator(_ptr-rhs.ptr);}
	    inline iterator operator+(difference_type rhs) const {return iterator(_ptr+rhs);}
	    inline iterator operator-(difference_type rhs) const {return iterator(_ptr-rhs);}
	    friend inline iterator operator+(difference_type lhs, const iterator& rhs) {return iterator(lhs+rhs._ptr);}
	    friend inline iterator operator-(difference_type lhs, const iterator& rhs) {return iterator(lhs-rhs._ptr);}

	    inline bool operator==(const iterator& rhs) const {return _ptr == rhs._ptr;}
	    inline bool operator!=(const iterator& rhs) const {return _ptr != rhs._ptr;}
	    inline bool operator>(const iterator& rhs) const {return _ptr > rhs._ptr;}
	    inline bool operator<(const iterator& rhs) const {return _ptr < rhs._ptr;}
	    inline bool operator>=(const iterator& rhs) const {return _ptr >= rhs._ptr;}
	    inline bool operator<=(const iterator& rhs) const {return _ptr <= rhs._ptr;}
	private:
    	T* _ptr;
	};

	typedef T value_type; 
	typedef unsigned long long size_type;
	
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef const iterator const_iterator;

	iterator begin() {
		return iterator(start);
	}

	const_iterator begin() const {
		return const_iterator(start);
	}

	iterator end() {
		return iterator(start + sz);		
	}

	const_iterator end() const {
		return const_iterator(start + sz);
	}
	
	reference operator[](size_type n) {
		return start[n];
	}

	const_reference operator[](size_type n) const {
		return start[n];
	}

	reference at(size_type n) {
		if (n < 0 || n >= sz) {
			throw std::out_of_range(" ");
		}
		return start[n];
	}

	const_reference at(size_type n) const {
		if (n < 0 || n >= sz) {
			throw std::out_of_range(" ");
		}
		return start[n];
	}

	reference front() {
		return start[0];
	}

	const_reference front() const {
		return start[0];
	}

	reference back() {
		return start[sz - 1];
	}

	const_reference back() const {
		return start[sz - 1];
	}

	vector() : start(nullptr), sz(0), cap(0) {}

	vector(size_type n, const T& val = T()) {
		start = new T[n];
		for(int i = 0; i < n; ++i) {
			start[i] = val;
		}
		sz = cap = n;
	}

	vector(const vector& x) {
		start = new T[x.cap];
		for(int i = 0; i < x.sz; ++i) {
			start[i] = x[i];
		}
		sz = x.sz;
		cap = x.cap;
	}
	
	~vector() {
		clear();
	}

	vector& operator=(const vector& x) {
		if(this != &x) {
			vector temp = x;
			clear();
			start = temp.start;
			sz = temp.sz;
			cap = temp.cap;
			temp.start = nullptr;
		}
		return *this;
	}

	void push_back(const T& x) {
		if (sz == cap) {
			reallocate();
		}
		++sz;
		start[sz - 1] = x;		
	}

	void pop_back() {
		if (sz != 0) {
			--sz;
		}
	}

	iterator insert(iterator pos, const T& x) {

	}

	void insert(iterator pos, size_type n, const T& x) {

	}
	
	iterator erase(iterator pos) {

	}
	iterator erase(iterator first, iterator last) {

	}
	
	void clear() {
		delete [] start;
	}

	size_type size() const {
		return sz;
	}

	bool empty() const { 
		return sz == 0; 
	}

	void resize(size_type sz, T val = T()) {

	}
	
	size_type capacity() const {
		return cap;
	}

	void reserve(size_type n) {
		if (n > cap) {
			reallocate(n);
		}
	}

private:
	size_type cap;
	size_type sz;
	pointer start;
	
	void reallocate(size_type n = 0) {
		size_type new_cap;
		if(n != 0) {
			new_cap = n;
		}
		else if(cap == 0) {
			new_cap = 1;
		}
		else {
			new_cap = 2 * cap;
		}

		T* temp_start = new T[new_cap];
		for(int i = 0; i < sz; ++i) {
			temp_start[i] = start[i];				
		}
		delete [] start;
		start = temp_start;
		cap = new_cap;
	}
};
