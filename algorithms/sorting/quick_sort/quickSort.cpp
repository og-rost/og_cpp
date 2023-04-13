#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <chrono>
#include <random>

using iter = std::vector<int>::iterator;

void myQuickSort(iter beg, iter end) { // optimize by taking median of 3 random items as pivot
    if (std::distance(beg, end) < 2) {
        return;
    }
    int pivot = *beg;
    iter i = beg + 1;
    iter j = end - 1;

    while (i <= j) {
        while (*i < pivot) ++i;
        while (*j > pivot) --j;
        if (i <= j) {
            std::swap(*i++, *j--);
        }
    }
    std::swap(*beg, *j);

    if (beg < j) {
        myQuickSort(beg, j + 1);
    }
    if (i < end) {
        myQuickSort(i, end);
    }
}


iter partition(iter begin, iter end) {
    int x = *(end - 1);
    iter i = begin - 1;
    for (iter j = begin; j < end - 1; ++j) {
        if (*j <= x)
            std::swap(*++i, *j);
    }
    std::swap(*++i, *(end - 1));
    return i;
}

void quickCormen(iter l, iter r) {
    if (l < r) {
        iter p = partition(l, r);
        quickCormen(l, p);
        quickCormen(p + 1, r);
    }
}

void quickIterative(iter left, iter right) {
    std::stack<iter> stk;
    stk.push(left);
    stk.push(right);

    while (!stk.empty()) {
        right = stk.top();
        stk.pop();
        left = stk.top();
        stk.pop();

        iter p = partition(left, right);

        if (p > left) {
            stk.push(left);
            stk.push(p);
        }

        if (p + 1 < right) {
            stk.push(p + 1);
            stk.push(right);
        }
    }
}

void test1(std::vector<int> vec) {
    std::chrono::high_resolution_clock::time_point t1, t2;
    std::chrono::nanoseconds timer;
    t1 = std::chrono::high_resolution_clock::now();

    std::sort(vec.begin(), vec.end());

    t2 = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::nanoseconds> (t2 - t1);

    std::cout << timer.count() << "  standard" << std::endl;
    std::cout << "Is sorted? " << std::is_sorted(vec.begin(), vec.end()) << std::endl;
}

void test2(std::vector<int> vec) {
    std::chrono::high_resolution_clock::time_point t1, t2;
    std::chrono::nanoseconds timer;
    t1 = std::chrono::high_resolution_clock::now();

    myQuickSort(vec.begin(), vec.end());

    t2 = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::nanoseconds> (t2 - t1);

    std::cout << timer.count() << "  mine" << std::endl;
    std::cout << "Is sorted? " << std::is_sorted(vec.begin(), vec.end()) << std::endl;
}

void test3(std::vector<int> vec) {
    std::chrono::high_resolution_clock::time_point t1, t2;
    std::chrono::nanoseconds timer;
    t1 = std::chrono::high_resolution_clock::now();

    quickCormen(vec.begin(), vec.end());

    t2 = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::nanoseconds> (t2 - t1);

    std::cout << timer.count() << "  Cormen" << std::endl;
    std::cout << "Is sorted? " << std::is_sorted(vec.begin(), vec.end()) << std::endl;
}

void test4(std::vector<int> vec) {
    std::chrono::high_resolution_clock::time_point t1, t2;
    std::chrono::nanoseconds timer;
    t1 = std::chrono::high_resolution_clock::now();

    quickIterative(vec.begin(), vec.end());

    t2 = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::nanoseconds> (t2 - t1);

    std::cout << timer.count() << "  iterative" << std::endl;
    std::cout << "Is sorted? " << std::is_sorted(vec.begin(), vec.end()) << std::endl;
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

    std::cout << "Testing quicksort for size " << vec.size() << std::endl;
    test1(vec);
    test2(vec);
    test3(vec);
    test4(vec);
    return 0;
}
