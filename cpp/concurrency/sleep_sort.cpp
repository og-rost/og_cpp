#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>


using iter = std::vector<int>::iterator;

void sleep_sort(iter start, iter end, std::vector<int>& res) {
    while (start != end) {
        std::thread([start, &res] () { std::this_thread::sleep_for(std::chrono::seconds(*start));
                                       res.push_back(*start); 
                                     }).detach();
        ++start;
    }
}

int main() {
    std::vector<int> vec = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector<int> res;

    std::thread sortThread(sleep_sort, vec.begin(), vec.end(), std::ref(res));
    sortThread.join();
    int max = *std::max_element(vec.begin(), vec.end());
    std::this_thread::sleep_for(std::chrono::seconds(max));

    for (int i : res) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}