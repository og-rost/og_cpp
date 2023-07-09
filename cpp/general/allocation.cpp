/*

std::pmr stands for Polymorphic Memory Resource, introduced in C++17 as part of the standard library.
It is designed to provide a uniform interface to customize the memory allocation strategy in C++ programs.

Old-style Allocators

In the STL (Standard Template Library), containers like std::vector, std::list, and std::map
have an Allocator template parameter that controls how they allocate and deallocate memory.

The default allocator is std::allocator.

*/

#include <memory_resource>
#include <vector>

#include <cstdlib>
#include <new>

void f1() {
    std::vector<int, std::allocator<int>> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
}

/*

Here, std::allocator allocates memory using ::operator new and deallocates memory using ::operator delete.

However, this model of allocators has several issues. For one, it's hard to write stateful allocators.
The model doesn't allow easy propagation of allocator instances through a program.

Also, an allocator type is part of the container type, which means that two containers of the same kind
but with different allocators are different types.

*/

// defining an old style allocator

template <class T>
class MyAllocator {
public:
    using value_type = T;

    MyAllocator() = default;

    template <class U> 
    constexpr MyAllocator(const MyAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        if(n > std::size_t(-1) / sizeof(T)) throw std::bad_alloc();
        if(auto p = static_cast<T*>(std::malloc(n*sizeof(T)))) return p;
        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t) noexcept { std::free(p); }
};

template <class T, class U>
bool operator==(const MyAllocator<T>&, const MyAllocator<U>&) { return true; }

template <class T, class U>
bool operator!=(const MyAllocator<T>&, const MyAllocator<U>&) { return false; }

/*

The operator== and operator!= functions are required to compare allocators for equality.
Two allocators a1 and a2 of the same type are equal if and only if the storage allocated
by a1 can be deallocated by a2, and vice versa.

*/

void ff() {
    std::vector<int, MyAllocator<int>> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
}


/*

std::pmr addresses the issues with old-style allocators by separating the memory resource
(which do the actual allocation and deallocation) from the polymorphic allocators.
The latter uses the former and can be rebound to any type.

*/


void f2() {
    std::pmr::monotonic_buffer_resource pool;
    std::pmr::vector<int> vec(&pool);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
}


/*

In this example, std::pmr::monotonic_buffer_resource is a kind of memory resource that uses a buffer
that grows as necessary to satisfy memory allocation requests.

std::pmr::vector is an alias template for std::vector that uses std::pmr::polymorphic_allocator.

*/

namespace std::pmr {
    template <typename T>
    using vector = std::vector<T, std::pmr::polymorphic_allocator<T>>;
}


// It is also possible to pass a polymorphic allocator directly to the vector

void f3() {
    std::pmr::polymorphic_allocator<int> alloc{std::pmr::get_default_resource()};
    std::vector<int, std::pmr::polymorphic_allocator<int>> vec{alloc};
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
}

/*

The important point is that memory resources are easily replaceable and customizable.
They can also be shared among containers and other data structures, unlike old-style allocators.

In summary, std::pmr is a great improvement over old-style allocators in C++, especially for programs
that need to customize memory allocation strategy. However, the old-style allocators are simpler
to use and still suitable for many programs that don't have special needs for memory allocation.

*/

/*

In the std::pmr namespace of C++, there are several types of predefined memory resources,
each of which provides a different memory allocation strategy.

1) std::pmr::new_delete_resource: This returns a pointer to a global object of a type derived
from std::pmr::memory_resource, suitable for use as the default memory resource,
which calls global new and delete for allocation and deallocation.

2) std::pmr::null_memory_resource: It always throws std::bad_alloc when requested to allocate memory.

3) std::pmr::unsynchronized_pool_resource: It uses a collection of pools representing different block sizes,
where each pool manages a set of chunks of memory. The block sizes increase roughly geometrically.

4) std::pmr::synchronized_pool_resource: It is similar to std::pmr::unsynchronized_pool_resource but is thread-safe.

5) std::pmr::monotonic_buffer_resource: It uses a single contiguous chunk of memory and simply
advances a pointer through the chunk as memory is allocated.

*/

void f4() {
    // Using synchronized_pool_resource
    std::pmr::synchronized_pool_resource pool;
    std::pmr::vector<int> vec1(&pool);
    vec1.push_back(1);

    // Using monotonic_buffer_resource
    char buffer[64] = {};
    std::pmr::monotonic_buffer_resource pool2(buffer, sizeof(buffer));
    std::pmr::vector<int> vec2(&pool2);
    vec2.push_back(2);
}


/*

To create your own memory pool, you can derive from std::pmr::memory_resource and override the
do_allocate
do_deallocate
do_is_equal

functions.

*/

class MyMemoryResource : public std::pmr::memory_resource {
protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        // Implement your custom allocation logic here
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        // Implement your custom deallocation logic here
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        // Two instances of MyMemoryResource are always equal
        return dynamic_cast<const MyMemoryResource*>(&other) != nullptr;
    }
};
