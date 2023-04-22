#include <algorithm>
#include <vector>
#include <iostream>

auto print_element = [](int element) {
    std::cout << element << " ";
};


template<class BidirIt>
bool my_next_permutation(BidirIt first, BidirIt last) {
    auto r_first = std::make_reverse_iterator(last);
    auto r_last = std::make_reverse_iterator(first);
    auto left = std::is_sorted_until(r_first, r_last);
    if(left != r_last){
        auto right = std::upper_bound(r_first, left, *left);
        std::iter_swap(left, right);
    }
    std::reverse(left.base(), last);
    return left != r_last;
}

    
int main() {
    std::vector<int> vec {1, 2, 3};
    do {
        std::for_each(vec.begin(), vec.end(), print_element);
        std::cout << std::endl;
    } while(my_next_permutation(vec.begin(), vec.end()));

    return 0;
}
