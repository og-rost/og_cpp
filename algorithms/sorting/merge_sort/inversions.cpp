//https://www.geeksforgeeks.org/counting-inversions/

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using iter = std::vector<int>::iterator;

int merge(iter left, iter mid, iter right) {
    std::vector<int> lvec, rvec;
    int inv = 0;
    iter temp = left;	
    while (temp <= mid) {
        lvec.push_back(*temp++);
    }
    while (temp <= right) {
        rvec.push_back(*temp++);
    }

    iter i = lvec.begin(), j = rvec.begin();
    while (i != lvec.end() && j != rvec.end()) {
        if (*i <= *j) {
            *left++ = *i++;
        }
        else {
            *left++ = *j++;
            inv = inv + std::distance(i, mid);
        }
    }
    while (i != lvec.end()) {
        *left++ = *i++;
    }
    while (j != rvec.end()) {
        *left++ = *j++;
    }

    return inv;
}

int mergeSort(iter b, iter e) {
    int inv = 0;
    if (b < e) {
        iter mid = b + (e - b) / 2;
        inv += mergeSort(b, mid);
        inv += mergeSort(mid + 1, e);
        inv += merge(b, mid, e);
    }
    return inv;
}


int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist2(300, 500);
    int tc = dist2(rng);
    std::cout << "algorithms will be tested " << tc << " times" << std::endl;
    while(tc--) {

        std::vector<int> vec;

        std::uniform_int_distribution<std::mt19937::result_type> dist1(300000, 500000);
        int size = dist1(rng);
        vec.resize(size);

        std::cout << "size is " << size<< std::endl;

        std::generate(vec.begin(), vec.end(), rand);
        if(std::is_sorted(vec.begin(), vec.end())) {
            std::cout << "########### vector is already sorted" << std::endl;
        }
        else {
            std::cout << "=========== vector is not sorted yet" << std::endl;
        }

        int inv = mergeSort(vec.begin(), vec.end());
        bool result = std::is_sorted(vec.begin(), vec.end());
        if(result) {
            std::cout << "=========== vector is sorted" << std::endl;
            std::cout << "=========== vector had " << inv << " inversions" << std::endl;
        }
        else {
            std::cout << "########### Error: vector is not sorted" << std::endl;
            std::cout << "########### Your merge sort algorithm sucks!" << std::endl;
            break;
        }
    }

    return 0;
}
