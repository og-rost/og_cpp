#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using iter = std::vector<int>::iterator;

void insertion_sort(iter beg, iter end) {
    for (auto it = beg + 1; it != end; ++it) {
        int key = *it;
        while(it != beg && key < *(it - 1)) {
            *it = *(it - 1);
            --it;
        }
        *it = key;
    }
}

int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> distSize(6000, 10000);
    int size = distSize(rng);

    std::uniform_int_distribution<int> distElem(-100000, 100000);

    auto gen = [&distElem, &rng]() { return distElem(rng); };

    std::vector<int> vec(size);
    std::generate(begin(vec), end(vec), gen);
    insertion_sort(vec.begin(), vec.end());
    std::cout << "Is sorted? " << std::is_sorted(vec.begin(), vec.end()) << std::endl;
}
