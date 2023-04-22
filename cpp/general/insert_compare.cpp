#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <random>


template<typename Container, typename Iterator>
void test(Container& cont, Iterator iter, int value) {
    std::cout << "Test time" << std::endl;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    cont.insert(iter, value);
    std::cout << std::chrono::duration_cast<std::chrono::duration<double,std::ratio<1>>>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
}


int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::vector<int> vec;
    std::uniform_int_distribution<size_t> distSize(10000000, 100000000);
    //std::uniform_int_distribution<int> distSize(100, 10000);
    int size = distSize(rng);
    vec.resize(size, 0);
    std::uniform_int_distribution<int> distElem(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    auto gen = [&distElem, &rng]() { return distElem(rng); };

    std::cout << "Generating vector of size: " << size << std::endl;
    std::generate(begin(vec), end(vec), gen);

    std::cout << "Copying the vector into list" << std::endl;
    std::list<int> lst(vec.begin(), vec.end());

    std::cout << "Printing sizes before" << std::endl;
    std::cout << vec.size() << std::endl;
    std::cout << lst.size() << std::endl;

    auto iter1 = vec.begin() + vec.size() / 2;
    auto iter3 = lst.begin();
    std::cout << "Finding list middle iterator" << std::endl;
    std::advance(iter3, lst.size() / 2);

    std::cout << "================= setup is done ==================" << std::endl;

    std::cout << "Testing for vector" << std::endl;
    test(vec, iter1, -69);
    std::cout << "Testing for list" << std::endl;
    test(lst, iter3, -69);

    std::cout << "Printing sizes after" << std::endl;
    std::cout << vec.size() << std::endl;
    std::cout << lst.size() << std::endl;

    std::cout << "Printing inserted values" << std::endl;

    iter1 = vec.begin();
    int diff = 1;
    if (vec.size() % 2 == 1) {
        --diff;
    }
    std::advance(iter1, vec.size() / 2 - diff);
    std::cout << *iter1 << std::endl;
    iter3 = lst.begin();
    std::advance(iter3, lst.size() / 2 - diff);
    std::cout << *iter3 << std::endl;
    return 0;
}
