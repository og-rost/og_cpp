// Atomic types are types that encapsulate a value whose access is 
// guaranteed to not cause data races and can be used to synchronize 
// memory accesses among different threads.

#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <sstream>        // std::stringstream
#include <atomic>         // std::atomic, std::memory_order_relaxed, std::atomic_flag
#include <syncstream>

struct Counter {
    int value;

    void increment() {
        ++value;
    }

    void decrement() {
        --value;
    }

    int get() {
        return value;
    }
};

// This class can be made thread safe using
// a) mutexes
// b) atomic


// The C++11 Concurrency Library introduces Atomic Types as a template class: 
// std::atomic. You can use any Type you want with that template and the operations 
// on that variable will be atomic and so thread-safe. It has to be taken into 
// account that it is up to the library implementation to choose which syncronization 
// mechanism is used to make the operations on that type atomic. On standard platforms 
// for integral types like int, long, float, ... it will be some lock-free technique. 
// If you want to make a big type (let's saw 2MB storage), you can use std::atomic as 
// well, but mutexes will be used. In this case, there will be no performance advantage.

// The main functions that std::atomic provide are the store and load functions that 
// atomically set and get the contents of the std::atomic. Another interesting function 
// is exchange, that sets the atomic to a new value and returns the value held previously. 
// Finally, there are also two functions compare_exchange_weak and compare_exchance_strong 
// that performs atomic exchange only if the value is equal to the provided expected value. 
// These two last functions can be used to implement lock-free algorithms.

// std::atomic is specialized for all integral types to provide member functions specific 
// to integral (like operators ++, --, fetch_add, fetch_sub, ...).

struct AtomicCounter {
    std::atomic<int> value{0};

    void increment() {
        ++value;
    }

    void decrement() {
        --value;
    }

    int get() {
        return value.load();
    }
};


// Atomic flag

// Atomic flags are boolean atomic objects that support two operations: 
// test-and-set and clear.

// Atomic flags are lock-free (this is the only type guaranteed to be lock-free 
// on all library implementations).



std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;

void append_number(int x) {
    while (lock_stream.test_and_set()) {}
    stream << "thread #" << x << std::endl;
    lock_stream.clear();
}

void atomic_flag() {
    std::vector<std::thread> threads;
    for (int i = 1; i <= 10; ++i) {
        threads.push_back(std::thread(append_number, i));
    }
    for (auto& th : threads) {
        th.join();
    }

    std::cout << stream.str();
}


std::atomic<int> foo(0);

void set_foo(int x) {
    foo.store(x, std::memory_order_relaxed);     // set value atomically
}

void print_foo() {
    int x;
    do {
        x = foo.load(std::memory_order_relaxed);  // get value atomically
    } while (x == 0);
    std::cout << "foo: " << x << std::endl;
}

void store_load() {
    std::thread first(print_foo);
    std::thread second(set_foo, 10);
    first.join();
    second.join();
}



void sync_output() {
    std::atomic<int> counter{0};
    std::thread t([&]() {
        while (counter.load() < 100) {
            std::osyncstream syncout{std::cout};
            syncout << "from thread " << ++counter << std::endl;
        }
    });

    while (counter.load() < 100) {
        std::osyncstream syncout{std::cout};
        syncout <<"from main " << ++counter << std::endl;
    }


    t.join();

    std::cout << counter << std::endl;
}

int main() {
    atomic_flag();
    store_load();
    sync_output();
    return 0;
}