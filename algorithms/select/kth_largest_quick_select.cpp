#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using iter = std::vector<int>::iterator;

iter partition(iter left, iter right) {
    int pivotVal = *right;
    iter runner = left;
    for (iter i = left; i < right; ++i) {
        if (*i < pivotVal) {
            std::swap(*runner, *i);
            ++runner;
        }
    }
    std::swap(*runner, *right);
    return runner;
}

int findKthLargest(std::vector<int> nums, int k) {
    if (nums.size() == 1) {
        return nums[0];
    }
    iter left = nums.begin();
    iter right = nums.end() - 1;
    iter targetIndex = nums.end() - k;
    
    while (left <= right) {
        iter pivot = partition(left, right);
        if (pivot < targetIndex) {
            left = pivot + 1;
        } else if (pivot > targetIndex) {
            right = pivot - 1;
        } else {
            return *pivot;
        }
    }
    return 0;
}

std::vector<int> generate_data() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist1(0, 100);
    std::uniform_int_distribution<int> dist2(1, 10);

    std::vector<int> data(dist2(rng));
    std::generate(data.begin(), data.end(), [&dist1, &rng]() { return dist1(rng); });
    return data;
}

int main() {
    int i = 10;
    while (i--) {
        std::vector<int> myVector = generate_data();
        int size = myVector.size();
        std::cout << "Median1: " << findKthLargest(myVector, size / 2) << std::endl;
        std::sort(myVector.begin(), myVector.end());
        std::cout << "Median2: " << myVector[myVector.size() / 2] << std::endl;
    }
    return 0;
}

// complexity

// partition is O(n)
// it calls partition for n -> n/2 -> n/4 ... -> 2n
// worst case -> it calls partition for n -> n-1 -> n-2 ... -> n^2