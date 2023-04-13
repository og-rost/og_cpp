#include <iostream>
#include <vector>
#include <iterator>


std::vector<int>::iterator partition(std::vector<int>::iterator low, std::vector<int>::iterator high) {
    int pivot = *high;
    auto i = low - 1;

    for (auto j = low; j != high; ++j) {
        if (*j < pivot) {
            ++i;
            std::swap(*i, *j);
        }
    }
    std::swap(*(i + 1), *high);
    return i + 1;
}

void quickSort(std::vector<int>::iterator low, std::vector<int>::iterator high) {
    if (low < high) {
        auto pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    quickSort(arr.begin(), arr.end() - 1);

    std::cout << "Sorted array: " << std::endl;
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return 0;
}
