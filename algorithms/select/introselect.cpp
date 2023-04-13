#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>

template <class Compare, class ForwardIterator>
constexpr unsigned sort3(ForwardIterator x, ForwardIterator y, ForwardIterator z, Compare comp) {
    unsigned retValue = 0;
    if (!comp(*y, *x)) {         // if x <= y
        if (!comp(*z, *y))      // if y <= z
            return retValue;            // x <= y && y <= z
                                   // x <= y && y > z
        std::swap(*y, *z);          // x <= z && y < z
        retValue = 1;
        if (comp(*y, *x))       // if x > y
        {
            std::swap(*x, *y);      // x < y && y <= z
            retValue = 2;
        }
        return retValue;                // x <= y && y < z
    }
    if (comp(*z, *y)) {          // x > y, if y > z
        std::swap(*x, *z);          // x < y && y < z
        retValue = 1;
        return retValue;
    }
    std::swap(*x, *y);              // x > y && y <= z
    retValue = 1;                       // x < y && x <= z
    if (comp(*z, *y)) {          // if y > z
        std::swap(*y, *z);          // x <= y && y < z
        retValue = 2;
    }
    return retValue;
}

// Assumes size > 0
template <class Compare, class BidirectionalIterator>
constexpr void selection_sort(BidirectionalIterator first, BidirectionalIterator last, Compare comp) {
    BidirectionalIterator runner = last;
    for (--runner; first != runner; ++first) {
        BidirectionalIterator minIter = std::min_element<BidirectionalIterator, Compare&>(first, last, comp);
        if (minIter != first)
            std::swap(*first, *minIter);
    }
}

template<class Compare, class RandomAccessIterator>
constexpr bool find_guard(RandomAccessIterator& i, RandomAccessIterator& j, RandomAccessIterator m, Compare comp) {
    // manually guard downward moving j against i
    while (true) {
        if (i == --j) {
            return false;
        }
        if (comp(*j, *m)) {
            return true;  // found guard for downward moving j, now use unguarded partition
        }
    }
}

template <class Compare, class RandomAccessIterator>
constexpr void introselect(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, Compare comp) {
    // _Compare is known to be a reference type
    typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
    const difference_type limit = 7;
    while (true) {
        if (nth == last)
            return;
        difference_type len = last - first;
        switch (len) {
        case 0:
        case 1:
            return;
        case 2:
            if (comp(*--last, *first))
                std::swap(*first, *last);
            return;
        case 3:
            RandomAccessIterator m = first;
            sort3<Compare>(first, ++m, --last, comp);
            return;
        }
        if (len <= limit) {
            selection_sort<Compare>(first, last, comp);
            return;
        }
        // len > limit >= 3
        RandomAccessIterator median = first + len / 2;
        RandomAccessIterator actualLast = last;
        unsigned __n_swaps = sort3<Compare>(first, median, --actualLast, comp);
        // partition [first, median) < *median and *median <= [median, last)
        // (this inhibits tossing elements equivalent to median around unnecessarily)
        RandomAccessIterator __i = first;
        RandomAccessIterator __j = actualLast;
        // j points beyond range to be tested, *actualLast is known to be <= *median
        // The search going up is known to be guarded but the search coming down isn't.
        // Prime the downward search with a guard.
        if (!comp(*__i, *median)) { // if *__first == *__m
            // *__first == *median, *__first doesn't go in first part
            if (find_guard<Compare>(__i, __j, median, comp)) {
                std::swap(*__i, *__j);
                ++__n_swaps;
            } else {
                // *__first == *median, *median <= all other elements
                // Partition instead into [__first, __i) == *__first and *__first < [__i, __last)
                ++__i;  // __first + 1
                __j = last;
                if (!comp(*first, *--__j)) {  // we need a guard if *__first == *(__last-1)
                    while (true) {
                        if (__i == __j) {
                            return;  // [__first, __last) all equivalent elements
                        } else if (comp(*first, *__i)) {
                            std::swap(*__i, *__j);
                            ++__n_swaps;
                            ++__i;
                            break;
                        }
                        ++__i;
                    }
                }
                // [__first, __i) == *__first and *__first < [__j, __last) and __j == __last - 1
                if (__i == __j) {
                    return;
                }
                while (true) {
                    while (!comp(*first, *__i))
                        ++__i;
                    while (comp(*first, *--__j));
                    if (__i >= __j)
                        break;
                    std::swap(*__i, *__j);
                    ++__n_swaps;
                    ++__i;
                }
                // [__first, __i) == *__first and *__first < [__i, __last)
                // The first part is sorted,
                if (nth < __i) {
                    return;
                }
                // __nth_element the second part
                // _VSTD::__nth_element<_Compare>(__i, __nth, __last, __comp);
                first = __i;
                continue;
            }
        }
        ++__i;
        // j points beyond range to be tested, *__lm1 is known to be <= *__m
        // if not yet partitioned...
        if (__i < __j)
        {
            // known that *(__i - 1) < *__m
            while (true)
            {
                // __m still guards upward moving __i
                while (comp(*__i, *median))
                    ++__i;
                // It is now known that a guard exists for downward moving __j
                while (!comp(*--__j, *median))
                    ;
                if (__i >= __j)
                    break;
                std::swap(*__i, *__j);
                ++__n_swaps;
                // It is known that __m != __j
                // If __m just moved, follow it
                if (median == __i)
                    median = __j;
                ++__i;
            }
        }
        // [__first, __i) < *__m and *__m <= [__i, __last)
        if (__i != median && comp(*median, *__i))
        {
            std::swap(*__i, *median);
            ++__n_swaps;
        }
        // [__first, __i) < *__i and *__i <= [__i+1, __last)
        if (nth == __i)
            return;
        if (__n_swaps == 0)
        {
            // We were given a perfectly partitioned sequence.  Coincidence?
            if (nth < __i)
            {
                // Check for [__first, __i) already sorted
                __j = median = first;
                while (true) {
                    if (++__j == __i) {
                        // [__first, __i) sorted
                        return;
                    }
                    if (comp(*__j, *median)) {
                        // not yet sorted, so sort
                        break;
                    }
                    median = __j;
                }
            }
            else
            {
                // Check for [__i, __last) already sorted
                __j = median = __i;
                while (true) {
                    if (++__j == last) {
                        // [__i, __last) sorted
                        return;
                    }
                    if (comp(*__j, *median)) {
                        // not yet sorted, so sort
                        break;
                    }
                    median = __j;
                }
            }
        }
        // __nth_element on range containing __nth
        if (nth < __i)
        {
            // _VSTD::__nth_element<_Compare>(__first, __nth, __i, __comp);
            last = __i;
        }
        else
        {
            // _VSTD::__nth_element<_Compare>(__i+1, __nth, __last, __comp);
            first = ++__i;
        }
    }
}



void printVec(const std::vector<int>& vec) {
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> v{5, 10, 6, 4, 3, 2, 6, 7, 9, 3};
    printVec(v);

    auto m = v.begin() + v.size() / 2;
    introselect(v.begin(), m, v.end(), std::less{});
    std::cout << "The median is " << v[v.size() / 2] << std::endl;
    printVec(v);

    // Note: comp function changed
    introselect(v.begin(), v.begin() + 1, v.end(), std::greater{});

    std::cout << "The second largest element is " << v[1] << std::endl;
    std::cout << "The largest element is " << v[0] << std::endl;
    printVec(v);
}


/*

nth_element is a partial sorting algorithm that rearranges elements in [first, last) such that:

The element pointed at by nth is changed to whatever element would occur in that position if [first, last) were sorted.
All of the elements before this new nth element are less than or equal to the elements after the new nth element.

*/
