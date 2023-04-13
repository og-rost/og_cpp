#include <algorithm>

// Assumes size > 0
template <class _Compare, class _BidirectionalIterator>
constexpr void selection_sort(_BidirectionalIterator __first, _BidirectionalIterator __last, _Compare __comp) {
    _BidirectionalIterator runner = __last;
    for (--runner; __first != runner; ++__first) {
        _BidirectionalIterator minIter = std::min_element<_BidirectionalIterator, _Compare&>(__first, __last, __comp);
        if (minIter != __first)
            std::swap(*__first, *minIter);
    }
}