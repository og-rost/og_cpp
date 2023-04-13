// Atomic types are types that encapsulate a value whose access is 
// guaranteed to not cause data races and can be used to synchronize 
// memory accesses among different threads.

#include <atomic>

struct Counter {
    int value;

    void increment(){
        ++value;
    }

    void decrement(){
        --value;
    }

    int get(){
        return value
    }
};

// This class van be made thread safe using
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
    std::atomic<int> value;

    void increment(){
        ++value;
    }

    void decrement(){
        --value;
    }

    int get(){
        return value.load();
    }
};
