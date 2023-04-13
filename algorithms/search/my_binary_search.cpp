#include <iostream>
#include <vector>

using iter = std::vector<int>::iterator;

iter bs(iter beg, iter end, int key) {
    iter temp_end = end;

    while (beg < end) {
        iter mid = beg + (end - beg) / 2;
        if (key == *mid) {
            return mid;
        }
        else if (key < *mid) {
            end = mid;
        }			
        else {
            beg = mid + 1;
        }
    }
    return temp_end;
}

int binary_search(const std::vector<int>& vec, int k) {
    if (vec.size() == 0) {
        return -1;
    }
    int start = 0;
    int end = vec.size() - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (vec[mid] == k) {
            return mid;
        }
        if (vec[mid] > k) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return -1;
}

int main() {
    return 0;
}
