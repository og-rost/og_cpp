#include <iostream>
#include <vector>

#define value_ty typename iter::value_type
#define vector_ty std::vector<value_ty> 

template <class T>
struct pred {
	bool operator()(const T& left, const T& right) const {
		return left < right;
	}
};

template<class iter, class Compare>
void make_heep(iter first, iter last, Compare comp) { 	
	for (int i = (last - first) / 2 - 1; i >= 0; --i) {
		heepify(first, last - first, i, comp);
	}
}

template<class iter, class Compare>
void heepify(iter first, int last, int parent, Compare comp) {

	int child = 2 * parent + 2;

	while (child < last) {
		if (comp(*(first + child), *(first + child - 1))) {
			--child;
		}
		if (comp(*(first + parent), *(first + child))) {
			std::swap(*(first + parent), *(first + child));
		}
		parent = child;
		child = 2 * parent + 2;
	}
}

template<class iter, class Compare>
void push_heep(iter first, int child, value_ty value, Compare comp) {
     
	int parent = (child - 1) / 2;
    
	while (child > 0 && comp(*(first + parent), value)) {
		  *(first + child) = *(first + parent);
		  child = parent;
		  parent = (child - 1) / 2;
	}      
	*(first + child) = value;
}

template <class T, class Container = std::vector<T>, 
class Compare = pred<typename Container::value_type>>
class priority_queue {
public:
	typedef priority_queue<T, Container, Compare> Myt;
	typedef Container container_type;
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type size_type;
	typedef typename Container::reference reference;
	typedef typename Container::const_reference const_reference;

	priority_queue() 
		: c(), comp()
	{
	}

	priority_queue(const Myt& other) 
		: c(other.c), comp(other.comp) 
	{
	}
	priority_queue(Myt&& other) 
		: c(std::move(other.c)), comp(other.comp) 
	{
	}
	explicit priority_queue(const Compare& comp)
		: c(), comp(comp)
	{	
	}
	priority_queue(const Compare& comp, const Container& Cont)
		: c(Cont), comp(comp) {
		make_heep(c.begin(), c.end(), comp);
	}
	template<class iter>
	priority_queue(iter First, iter Last)
		: c(First, Last) {
			make_heep(c.begin(), c.end(), comp);
	}

	template<class iter>
	priority_queue(iter First, iter Last, const Compare& comp)
		: c(First, Last), comp(comp) {
			make_heep(c.begin(), c.end(), comp);
	}

	template<class iter>
	priority_queue(iter First, iter Last, const Compare& comp, const Container& Cont)
		: c(Cont), comp(comp) {	
			c.insert(c.end(), First, Last);
			make_heep(c.begin(), c.end(), comp);
	}
 
	Myt& operator=(const Myt& rhs) {
		c = rhs.c;
		comp = rhs.comp;
		return *this;
	}

	Myt& operator=(Myt&& rhs) {
		c = rhs.c;
		comp = std::move(rhs.comp);
		return *this;
	}

	bool empty() const {
		return c.empty();
	}
	size_type size() const {
		return c.size();
	}

	const_reference top() const	{
		return (c.front());
	}

	reference top()	{
		return (c.front());
	}

	void push(const value_type& Val) {
		c.push_back(Val);
		push_heep(c.begin(), size() - 1, Val, comp);
	}

	void push(value_type&& Val) {
		c.push_back(Val);
		push_heep(c.begin(), size() - 1, Val, comp);
	}

	void pop() {
		pop_heep(c.begin(), c.end(), c.end() - 1, comp);
		c.pop_back();
	}

	void swap(Myt& Right) {
		std::swap(c, Right.c);
	}

protected:
	Container c;
	Compare comp;
};

template<class iter, class Compare>
void pop_heep(iter first, iter last,  iter result, Compare comp) {
    value_ty value = *result;
    *result = *first;
    adjust_heep(first, last - first - 1, value, comp);
}

template<class iter, class Compare>
 void heep_sort(iter first, iter last, Compare comp) {
	make_heep(first, last, comp);
	while (last - first) {
		pop_heep(first, last, last - 1, comp);
		--last; 
	}
}

 template<class iter>
 void heep_sort(iter first, iter last) {
	heep_sort(first, last, pred<value_ty>());
}

template<typename iter, typename Compare>
void adjust_heep(iter first, int n, value_ty& val, Compare comp)	{	
		
	int parent = 0;
	int child = 2;
			
	while (child < n) {				
			
		if (comp(*(first + child), *(first + (child - 1)))) {
			--child;
		}

		*(first + parent) = *(first + child);

		parent = child;
		child = 2 * parent + 2;
	}
	
	if (child == n) {				
		*(first + parent) = (*(first + (n - 1)));
		parent = n - 1;
	}
	
	push_heep(first, parent, val, comp);
}

template<class iter>
void quick_sort(iter first, iter last) { 
	merge_sort(first, last, pred<value_ty>());
}


template<class iter, class Compare>
void quick_sort(iter first, iter last, Compare functor) {
 
	value_ty pivot = *(first + (last - first) / 2);
	iter left = first;
	iter right = last - 1;

	while (left <= right) {

		while (functor(*left, pivot)) {
			++left;
		}
		while (functor(pivot, *right)) {
			--right;
		}	
		if (left <= right) {
			std::swap(*left++, *right--);
		}
	}

	if (left < last) {
		quick_sort(left, last, functor);
	}
	if (right > first) {
		quick_sort(first, right + 1, functor);
	}
}

template<class iter, class Compare>
void mergeing(iter first, vector_ty left, vector_ty right, Compare functor) {
	
	int i = 0, j = 0;

	while (i < left.size() && j < right.size()) {
		if (functor(left[i], right[j])) {
			*first++ = left[i++];
		} 
		else {
			*first++ = right[j++];
		}
	}
	while (i < left.size()) {
		*first++ = left[i++];
	}
	while (j < right.size()) {
		*first++ = right[j++];
	}
}

template<class iter>
void merge_sort(iter first, iter last) {
	merge_sort(first, last, pred<value_ty>());
}

template<class iter, class Compare>
void merge_sort(iter first, iter last, Compare functor) {

	if (first + 1 == last) {
		return;
	}
	vector_ty left(first, (first + (last - first) / 2));
	vector_ty right((first + (last - first) / 2), last);

	merge_sort(left.begin(),  left.end(),  functor);
	merge_sort(right.begin(), right.end(), functor);
	mergeing(first, left, right, functor);

}

template<class iter>
void insertion_sort(iter first, iter last) {
	insertion_sort(first, last, pred<value_ty>());
}


template<class iter, class Compare>
void insertion_sort(iter first, iter last, Compare functor) {
	
	if (first == last) {
		return;
	}
	value_ty key; 
	for (iter j, i = first; ++i != last; ) {
		key = *i;
		for (j = i; j != first && functor(key, *(j - 1)); --j) {
			*j = *(j - 1);
		}
		*j = key;
	}
}

template<class iter>
void sort_hybrid(iter first, iter last) {

	if (last - first < 25) {
		insertion_sort(first, last, pred<value_ty>());
		return;
	}

	value_ty pivot = *(first + (last - first) / 2);
	iter left = first;
	iter right = last - 1;
	pred<value_ty> functor;
	while (left <= right) {

		while (functor(*left, pivot)) {
			++left;
		}
		while (functor(pivot, *right)) {
			--right;
		}	
		if (left <= right) {
			std::swap(*left++, *right--);
		}
	}

	if (left < last) {
		sort_hybrid(left, last);
	}
	if (right > first) {
		sort_hybrid(first, right + 1);
	}
}

template<class iter>
void bubble_sort(iter first, iter last) {
	bubble_sort(first, last, pred<value_ty>());
}

template<class iter, class Compare>
void bubble_sort(iter first, iter last, Compare functor) {

	bool flag = true;
	for (iter i = first; flag && i != last; ++i) {
		flag = false;
		for (iter j = i + 1; j != last; ++j) {
			if (functor(*j, *i)) {
				std::swap(*i, *j);
				flag = true;
			}
		}
	}
}

template<class iter>
void solution_sort(iter first, iter last) {
	solution_sort(first, last, pred<value_ty>());
}

template<class iter, class Compare>
void solution_sort(iter first, iter last, Compare functor) {

	int index = 0;
	for (iter i = first, j; i != last; ++i) {
		index = (i - first);
		for (j = i + 1; j != last; ++j) {
			if (functor(*j, *(first + index))) {
				index = (last - (first + (last - j)));
			}
		}
		std::swap(*i, *(first + index));
	}
}