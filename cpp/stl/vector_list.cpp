/////////////////////////////////////////////////////////////////////
// Generate N random integers and insert them into a sequence so that
// each is inserted in its proper position in the numerical order.
// Example for generated sequence: 5 1 4 2
// 5
// 1 5
// 1 4 5
// 1 2 4 5
// Remove elements one at a time by picking a random position in the
// sequence and removing the element there. Positions 1 2 0 0 gives
// 1 2 4 5
// 1 4 5
// 1 4
// 4
/////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream> 
#include <iomanip> 
#include <vector> 
#include <chrono> 
#include <random>
#include <list> 

const int N = 20000;
using ms = std::chrono::milliseconds;

int random(int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> d(0, N);
    return d(gen);
}

template<class Container>
auto grow(Container& c) {
    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < N; ++i) {
        auto pos = c.begin();
        auto r = random(N);
        while (pos != c.end() && r > *pos) {
            ++pos;
        }
        c.insert(pos, r);
    }

    auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<ms>(end - start).count();
}

template<class Container>
auto shrink(Container& c) {
    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < N; ++i) {
        auto pos = c.begin();
        auto r = random(c.size() - 1);
        while (r--) ++pos;
        c.erase(pos);
    }

    auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<ms>(end - start).count();
}

int main() {
    std::vector<int> vector;
    std::list<int>   list;

    std::cout << "When N = " << N << std::endl << std::endl;

    auto v_grow   = grow(vector);   // time to grow
    auto v_shrink = shrink(vector); // time to shrink
    std::cout << "Vector" << std::endl;
    std::cout << "    Insertion: " << std::setw(7) << v_grow              << std::setfill(' ') << " ms" << std::endl;
    std::cout << "    Deletion:  " << std::setw(7) << v_shrink            << std::setfill(' ') << " ms" << std::endl;
    std::cout << "    Total:     " << std::setw(7) << (v_grow + v_shrink) << std::setfill(' ') << " ms" << std::endl;

    std::cout << std::endl;

    auto l_grow   = grow(list);     // time to grow
    auto l_shrink = shrink(list);   // time to shrink
    std::cout << "List" << std::endl;;
    std::cout << "    Insertion: " << std::setw(7) << l_grow              << std::setfill(' ') << " ms" << std::endl;
    std::cout << "    Deletion:  " << std::setw(7) << l_shrink            << std::setfill(' ') << " ms" << std::endl;
    std::cout << "    Total:     " << std::setw(7) << (l_grow + l_shrink) << std::setfill(' ') << " ms" << std::endl;

    std::cout << "Vector faster: x" << (double)(l_grow + l_shrink) / (v_grow + v_shrink) << std::endl;
}
