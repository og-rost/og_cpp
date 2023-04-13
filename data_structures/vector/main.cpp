#include "vector.hpp"
#include <iostream>

int main() {
    vector<int> vec;
    std::cout << vec.size() << "  " << vec.capacity() << std::endl;
    vec.push_back(42);
    std::cout << vec.front() << "  " << vec.back() << std::endl;
    std::cout << vec.size() << "  " << vec.capacity() << std::endl;
    vec.push_back(52);
    std::cout << vec.front() << "  " << vec.back() << std::endl;
    std::cout << vec.size() << "  " << vec.capacity() << std::endl;
    vec.push_back(62);
    std::cout << vec.front() << "  " << vec.back() << std::endl;
    std::cout << vec.size() << "  " << vec.capacity() << std::endl;
    vec.push_back(72);
    std::cout << vec.front() << "  " << vec.back() << std::endl;
    std::cout << vec.size() << "  " << vec.capacity() << std::endl;
    vec.push_back(82);
    std::cout << vec.front() << "  " << vec.back() << std::endl;
    std::cout << vec.size() << "  " << vec.capacity() << std::endl;

    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << "  ";
    }
    std::cout << std::endl;

    std::cout << vec.front() << "  " << vec.back() << std::endl;
}
