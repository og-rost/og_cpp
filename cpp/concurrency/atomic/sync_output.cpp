#include <iostream>
#include <thread>
#include <atomic>
#include <syncstream>

int main() {
    std::atomic<int> counter = 0;
    std::thread t([&]() {
        while (counter.load() < 100) {
            std::osyncstream syncout{std::cout};
            syncout << "from thread " << ++counter << '\n';
        }
    });

    while (counter.load() < 100) {
        std::osyncstream syncout{std::cout};
        syncout <<"from main " << ++counter << '\n';
    }


    t.join();

    std::cout << counter << std::endl;

    return 0;
}