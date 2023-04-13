#include <iostream>
#include <vector>
#include <random>

void heapify(std::vector<int>& vec, int i, int size) {
    while (i * 2 + 1 < size) {
        int child = 2 * i + 1;
        if (child + 1 < size && vec[child] < vec[child + 1]) {
            ++child;
        }

        if (vec[i] < vec[child]) {
            std::swap(vec[child], vec[i]);
            i = child;
        } else {
            return;
        }
    }
}

void heapsort(std::vector<int>& vec, int size) {
    for (int i = size / 2; i >= 0; --i) {
        heapify(vec, i, size);
    }

    while (size > 1) {
        std::swap(vec[size - 1], vec[0]);
        heapify(vec, 0, --size);
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

    heapsort(vec, vec.size());

    if (std::is_sorted(vec.begin(), vec.end())) {
        std::cout << "Sorted" << std::endl;
    }
    else {
        std::cout << "Not sorted" << std::endl;
    }

    return 0;
}