/*

In statistics and probability theory, the median is the value separating the higher half from the lower half of a data.
For a data set, it may be thought of as "the middle" value. Compared to the average, the median is not skewed by a small
proportion of extremely large or small values, and therefore provides a better representation of the center.

Median of median algorithm is most commonly used quickselect, that selects the kth smallest element of an initially unsorted array.
It can also be used as a pivot strategy in quicksort.

Worst-case performance - O(n)
Best-case performance - O(n)
Worst-case space complexity - O(log n)

*/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <vector>


int partition(std::vector<int>& nums, int left, int right, int pivot_index) {
    int pivot = nums[pivot_index];
    // move pivot to end
    std::swap(nums[pivot_index], nums[right]);
    int store_index = left;

    // move all smaller elements to the left
    for (int i = left; i <= right; ++i) {
        if (nums[i] < pivot) {
            std::swap(nums[store_index++], nums[i]);
        }
    }

    // move pivot to its final place
    std::swap(nums[store_index], nums[right]);

    return store_index;
}

int quickselect(std::vector<int> nums, int left, int right, int k_smallest) {
    // base case when the list contains only one element
    if (left == right) {
        return nums[left];
    }

    // select a random pivot_index
    // int pivot_index = left + (right - left) / 2; 
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(left, right);
    int pivot_index = dist(rng);
    
    pivot_index = partition(nums, left, right, pivot_index);

    // the pivot is on (N - k)th smallest position
    if (k_smallest == pivot_index) {
        return nums[k_smallest];
    }
    // go left side
    else if (k_smallest < pivot_index) {
        return quickselect(nums, left, pivot_index - 1, k_smallest);
    }
    // go right side
    return quickselect(nums, pivot_index + 1, right, k_smallest);
}

std::vector<int> generate_data() {
    std::random_device dev;
    std::mt19937 rng(dev());
    //std::uniform_int_distribution<int> dist1(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
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
        std::cout << "Median1: " << quickselect(myVector, 0, size - 1, size / 2) << std::endl;
        std::sort(myVector.begin(), myVector.end());
        std::cout << "Median2: " << myVector[myVector.size() / 2] << std::endl;
    }
    return 0;
}

// complexity

// partition is O(n)
// it calls partition for n -> n/2 -> n/4 ... -> 2n
// worst case -> it calls partition for n -> n-1 -> n-2 ... -> n^2