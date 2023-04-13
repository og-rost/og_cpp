#include <iostream>
#include <vector>
#include <algorithm>

template<typename ForwardIt, typename T>
bool bs(ForwardIt first, ForwardIt last, const T& value) {
    first = std::lower_bound(first, last, value);
    return (!(first == last) && !(value < *first));
}

template <typename T>
bool comp(const T& a, const T& b) {
    return a < b;
}

template<typename ForwardIt, typename T, typename Compare>
bool bs(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
    first = std::lower_bound(first, last, value, comp);
    return (!(first == last) && !(comp(value, *first)));
}

int main() {	
    std::vector<int> v;	
    for (int i = 0; i < 10000; ++i) {
        v.push_back(i);
    }

    bs(v.begin(), v.end(), 41);
    bs(v.begin(), v.end(), 42, comp<int>);

    return 0;
}
