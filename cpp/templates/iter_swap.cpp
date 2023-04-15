// attempt 1

template <class ForwardIterator>
void iter_swap(ForwardIterator i1, ForwardIterator i2) {
    T tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
}

// problem: what is T


// attempt 2
template <class ForwardIterator>
void iter_swap(ForwardIterator i1, ForwardIterator i2) {
    typename ForwardIterator::value_type tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
}

// problem: iterators in C++ are modeled on the design of pointers

void f(int* p1, int* p2) {
    iter_swap(p1, p2); // error: int* has no member 'value_type'
}



// Solution


// We may not be able to add a nested ::value_type to all iterators,
// but we can add it to a template that takes the iterator type as a parameter.

template <class Iterator> struct iterator_traits;

template <class ForwardIterator>
void iter_swap(ForwardIterator i1, ForwardIterator i2) {
    typename iterator_traits<ForwardIterator>::value_type tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
}

// the traits being described in iterator_traits are the iterator's five associated types:
// value_type, reference, pointer, difference_type, and iterator_category.


// the standard library contains the following partial specialization of iterator_traits,
// which describes the value_type of all pointers

template <class T>
struct iterator_traits<T*> {
    typedef T value_type;
    // four more typedefs
};


// The standard library provides a shortcut that allows the author of an iterator
// to control the types nested in its iterator_traits justv by writing member types in the iterator.


template <class Iterator>
struct iterator_traits {
    typedef typename Iterator::value_type value_type;
    // four more typedefs
};