#include <iostream>
#include <vector>

#define size 8

using iter = std::vector<int>::iterator;
 
int getMax(iter beg, iter end) {
    int max = *beg;
    for (iter i = beg + 1; i != end; ++i) {
        if (*i > max) {
            max = *i;
        }
    }
    return max;
} 

void countSort(std::vector<int>& output, std::vector<int>& count, int exp) {
    for (int i = 0; i < size; ++i) {
        count[(arr[i]/exp)%10]++; 
    }

    for (int i = 1; i < size+2; ++i) {
        count[i] += count[i - 1];
    }
 
    for (int i = size - 1; i >= 0; --i) {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
 
    for (int i = 0; i < size; ++i) {
        arr[i] = output[i];
    }
}

void radix(iter beg, iter end) {
    std::vector<int> output;
    output.reserve(std::distance(beg, end));
    std::vector<int> count;
    count.reserve(std::distance(beg, end) + 2);
    int m = getMax(beg, end);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSort(output, count, exp);
    }
}

int main() {
    td::vector<int> vec{170, 45, 75, 90, 802, 24, 2, 66};    
    radix(vec.begin(), vec.end());
    for (int i : vec) {
        std::cout << i << " ";
    }
	std::cout << std::endl;
    return 0;
}
