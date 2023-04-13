#include <iterator>

template <class _Compare, class _BidirectionalIterator>
void insertion_sort(_BidirectionalIterator __first, _BidirectionalIterator __last, _Compare __comp) {
    typedef typename std::iterator_traits<_BidirectionalIterator>::value_type value_type;
    if (__first != __last) {
        _BidirectionalIterator __i = __first;
        for (++__i; __i != __last; ++__i) {
            _BidirectionalIterator __j = __i;
            value_type __t(std::move(*__j));
            for (_BidirectionalIterator __k = __i; __k != __first && __comp(__t,  *--__k); --__j)
                *__j = std::move(*__k);
            *__j = std::move(__t);
        }
    }
}