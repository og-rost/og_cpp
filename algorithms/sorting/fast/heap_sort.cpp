#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using iter = std::vector<int>::iterator;

void heapify(iter beg, size_t i, size_t size) {
    while (i * 2 + 1 < size) {
        size_t child = 2 * i + 1;
        if (child + 1 < size && *(beg + child) < *(beg + child + 1)) {
            ++child;
        }
        if (*(beg + i) < *(beg + child)) {
            std::swap(*(beg + child), *(beg + i));
            i = child;
        }
        else return;
    }
}

void heap_sort(iter beg, iter end) {
    size_t size = std::distance(beg, end);
    for (int i = size / 2; i >= 0; --i) {
        heapify(beg, size_t(i), size);
    }

    while (size > 1) {
        std::swap(*(beg + size - 1), *beg);
        heapify(beg, 0, --size);
    }
}

int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> distSize(600000, 1000000);
    int size = distSize(rng);

    std::uniform_int_distribution<int> distElem(-1000000, 1000000);

    auto gen = [&distElem, &rng]() { return distElem(rng); };

    std::vector<int> vec(size);
    std::generate(begin(vec), end(vec), gen);

    heap_sort(vec.begin(), vec.end());

    if (std::is_sorted(vec.begin(), vec.end())) {
        std::cout << "Sorted" << std::endl;
    }
    else {
        std::cout << "Not sorted" << std::endl;
    }

    return 0;
}