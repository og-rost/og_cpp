#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// returns iterator pointing to the first element that is not less than value,
// or last if no such element is found.

template<class ForwardIt, class T>
ForwardIt lower(ForwardIt first, ForwardIt last, const T& value) {

    ForwardIt it;
    typename std::iterator_traits<ForwardIt>::difference_type count, step;
    count = std::distance(first, last);

    while (count > 0) {
        it = first; 
        step = count / 2; 
        std::advance(it, step);
        if (*it < value) {
            first = ++it; 
            count -= step + 1; 
        }
        else {
            count =	step;
        }
    }
    return first;
}

// returns iterator pointing to the first element that is greater than value
// or last if no such element is found.

template<class ForwardIt, class T>
ForwardIt upper(ForwardIt first, ForwardIt last, const T& value) {

    ForwardIt it;
    typename std::iterator_traits<ForwardIt>::difference_type count, step;
    count = std::distance(first,last);

    while (count > 0) {
        it = first; 
        step = count / 2; 
        std::advance(it, step);
        if (!(value < *it)) {
            first = ++it;
            count -= step + 1;
        }
        else {
            count = step;
        }
    }
    return first;
}

void print_lower_upper(const std::vector<int>& vec, int i) {
    std::cout << i << std::endl;
    std::cout << "standard lower " << *std::lower_bound(vec.begin(), vec.end(), i) << std::endl;
    std::cout << "lower "           << *lower(vec.begin(), vec.end(), i) << std::endl;
    std::cout << "standard upper " << *std::upper_bound(vec.begin(), vec.end(), i) << std::endl;
    std::cout << "upper "           << *upper(vec.begin(), vec.end(), i) << std::endl;
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {3, 4, 5, 5, 5, 5, 6, 7};

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    for(auto i : vec) {
        print_lower_upper(vec, i);
    }

    print_lower_upper(vec, 0);
    print_lower_upper(vec, 1);
    print_lower_upper(vec, 7);

    return 0;
}

