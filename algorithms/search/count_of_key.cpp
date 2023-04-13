#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using iter = std::vector<int>::const_iterator;

unsigned int count(const std::vector<int>& vec, int x) {
    iter i = std::lower_bound(vec.cbegin(), vec.cend(), x);
    iter j = std::upper_bound(vec.cbegin(), vec.cend(), x);

    if(i == vec.cend() && j == vec.cend()) {
        return 0;
    }
    return std::distance(i, j);
}

int main() {
    std::vector<int> vec = {3, 3, 4, 5, 5, 5, 5, 6, 7, 7, 7, 7, 8};

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    for (int i = 0; i < 10; ++i) {
        std::cout << "count of " << i << " in vector is " << count(vec, i) << std::endl;
    }
    return 0;
}
