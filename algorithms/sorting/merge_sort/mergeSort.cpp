#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <random>

using namespace std::chrono;
using nano = std::chrono::nanoseconds;  
using iter = std::vector<int>::iterator;

void merge(iter left, iter mid, iter right) {
    std::vector<int> lvec, rvec;
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
        }
    }
    while (i != lvec.end()) {
        *left++ = *i++;
    }
    while (j != rvec.end()) {
        *left++ = *j++;
    }
}

void mergeSortRecursive(iter b, iter e) {
    if (b < e) {
        iter mid = b + (e - b) / 2;
        mergeSortRecursive(b, mid);
        mergeSortRecursive(mid + 1, e);
        merge(b, mid, e);
    } 
}

void mergeSortIterative(iter b, iter e) {
    int d = 1;
    while(d < std::distance(b, e)) {
        iter temp = b;
        while(temp < e) {
            iter t = temp;
            std::vector<int> lvec, rvec;

            for(int i = 0; i < d && temp != e; ++i) {
                lvec.push_back(*temp++);
            }
            for(int i = 0; i < d && temp != e; ++i) {
                rvec.push_back(*temp++);
            }

            iter i = lvec.begin(), j = rvec.begin();
            while (i != lvec.end() && j != rvec.end()) {
                if (*i <= *j) {
                    *t++ = *i++;
                }
                else {
                    *t++ = *j++;
                }
            }

            while (i != lvec.end()) {
                *t++ = *i++;
            }
            while (j != rvec.end()) {
                *t++ = *j++;
            }
        }
        d = d * 2;		
    }
}

int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist2(300, 500);
    int tc = dist2(rng);
    std::cout << "algorithms will be tested " << tc << " times" << std::endl;
    while(tc--) {

        std::vector<int> vec1;

        std::uniform_int_distribution<std::mt19937::result_type> dist1(300000, 500000);
        int size = dist1(rng);
        vec1.resize(size);

        std::cout << "size is " << size<< std::endl;

        std::generate(vec1.begin(), vec1.end(), rand);
        std::vector<int> vec2 = vec1;
        if(std::is_sorted(vec1.begin(), vec1.end())) {
            std::cout << "########### vector is already sorted" << std::endl;
        }
        else {
            std::cout << "=========== vector is not sorted yet" << std::endl;
        }

        high_resolution_clock::time_point t1, t2;

        t1 = high_resolution_clock::now();
        mergeSortRecursive(vec1.begin(), vec1.end());
        t2 = high_resolution_clock::now();
        nano time1 = std::chrono::duration_cast<nano> (t2 - t1);
        bool result = std::is_sorted(vec1.begin(), vec1.end());
        if(result) {
            std::cout << "=========== vector 1 is sorted" << std::endl;
        }
        else {
            std::cout << "########### Error: vector 1 is not sorted" << std::endl;
            std::cout << "########### Your recursive algorithm sucks!" << std::endl;
            break;
        }
        std::cout << time1.count() << "    recursive" << std::endl;

        t1 = high_resolution_clock::now();
        mergeSortIterative(vec2.begin(), vec2.end());
        t2 = high_resolution_clock::now();
        nano time2 = std::chrono::duration_cast<nano> (t2 - t1);
        result = std::is_sorted(vec2.begin(), vec2.end());
        if(result) {
            std::cout << "=========== vector 2 is sorted" << std::endl;
        }
        else {
            std::cout << "########### Error: vector 2 is not sorted" << std::endl;
            std::cout << "########### Your iterative algorithm sucks!" << std::endl;
            break;
        }
        std::cout << time2.count() << "    iterative" << std::endl;
    }

    return 0;
}
