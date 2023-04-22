#include <iostream>
#include <memory>
#include <initializer_list>

using pair = std::pair<int*, int*>;

class vector {
private:
    std::allocator<int> alloc; 
	void chk_n_alloc() { 
		if (size() == capacity()) {
			reallocate();
        }
	}

	pair alloc_n_copy (const int*, const int*);
	void free();   
    void reallocate(); 
    int* data; 
    int* first_free; 
    int* cap; 
public:
	vector() : data(nullptr), first_free(nullptr), cap(nullptr) {}
	vector(const vector&);
	vector(vector&&);
	vector(std::initializer_list<int>);
	vector& operator=(const vector&);
	vector& operator=(vector&&);
	vector& operator=(std::initializer_list<int>);   
	~vector() { 
        free(); 
    }

	void push_back(const int&); 
    void push_back(int&&);
    void pop_back();

	size_t size() const { 
        return first_free - data; 
    }

    size_t capacity() const	{ 
        return cap - data;
    }
	
	int* begin() const { 
        return data; 
    }

	int* end() const { 
        return first_free; 
    }    
	
	int& operator[](size_t n) {
        return data[n]; 
    }

	const int& operator[](size_t n) const {
        return data[n]; 
    }

	template <class... Args>
	void emplace_back(Args&&...);
};

pair vector::alloc_n_copy(const int* b, const int* e) {
	int* start = alloc.allocate(e - b); 	
	int* after = std::uninitialized_copy(b, e, start);
	return pair(start, after); 
}

vector::vector(const vector& rhs) {	
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	data = newdata.first; 
	first_free = cap = newdata.second;
}

vector::vector(vector&& temp) : data(temp.data), first_free(temp.first_free), cap(temp.cap) {
	temp.data = temp.first_free = temp.cap = nullptr;
}

vector::vector(std::initializer_list<int> il) {	
	auto newdata = alloc_n_copy(il.begin(), il.end());
	data = newdata.first;
	first_free = cap = newdata.second;
}

vector& vector::operator=(const vector& rhs) {
	auto d = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	data = d.first;
	first_free = cap = d.second;
	return *this;
}

vector& vector::operator=(vector&& rhs) {
	if (this != &rhs) {
		free();  
		data = rhs.data; 
		first_free = rhs.first_free;
		cap = rhs.cap;	
		rhs.data = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

vector& vector::operator=(std::initializer_list<int> il) {	
	auto d = alloc_n_copy(il.begin(), il.end());
	free(); 
	data = d.first;
	first_free = cap = d.second;
	return *this;
}

void vector::free() {
	if (data) {
		for (int* p = first_free; p != data;) {
			alloc.destroy(--p);
        }
		alloc.deallocate(data, cap - data);
	}
}
	
void vector::reallocate() {
    size_t newcap = size() ? 2 * size() : 1;	
	auto newdata = alloc.allocate(newcap);
	auto start = newdata;
    auto elem = data;
	for (size_t i = 0; i != size(); ++i) {
		alloc.construct(start++, std::move(*elem++));
    }
	free();  
    data = newdata;
    first_free = start;
    cap = data + newcap;
}

void vector::push_back(const int& s) {
    chk_n_alloc();  
    alloc.construct(first_free++, s);  
}

void vector::push_back(int&& s) {
    chk_n_alloc(); 
	alloc.construct(first_free++, std::move(s));	
}

void vector::pop_back() {
	if (data) {
		alloc.destroy(--first_free);
    }
}

template <class... Args>
void vector::emplace_back(Args&&... args) {
    chk_n_alloc(); 
	alloc.construct(first_free++, std::forward<Args>(args)...);
}

int main() {
	vector vec;
	vec.push_back(100);
	vec.push_back(200);
	vec.push_back(300);
	vec.push_back(400);	
	vec.pop_back();
	vec.push_back(500);
	vec.emplace_back(600);
	for (int* p = vec.begin(); p != vec.end(); ++p) {
		std::cout << *p << "  ";
    }
    std::cout << std::endl;
	return 0;
}
