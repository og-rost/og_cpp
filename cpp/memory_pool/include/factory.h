#pragma once

#include <functional>
#include <iostream>

#include "controller.h"
#include "object_child1.h"
#include "object_child2.h"
#include "object_child3.h"

template<typename T>
std::pair<void*, std::function<void()>>
allocate_auto_memory(MemoryPoolPtr_t pool, std::string deallocMsg) {
    void* memAddr = pool->allocate(sizeof(T));
    pool->AddToObjectCounter(std::string(typeid(T).name()));

    auto deallocator = [memAddr, pool, deallocMsg] () {
	    std::cout << deallocMsg << std::endl;
        static_cast<T*>(memAddr)->~T();
        pool->deallocate(memAddr, sizeof(T));
    };

    return std::make_pair(memAddr, deallocator);
}


auto create_child1(Controller& controller, std::string name) {
    auto mem = allocate_auto_memory<ObjectChild1>(controller.get_memory_pool(), std::string("Deallocating ObjectChild1 object"));
    return std::shared_ptr<ObjectChild1>(new (mem.first) ObjectChild1(name), [mem](auto p) { mem.second(); });
}

auto create_child2(Controller& controller, std::string name) {
    auto mem = allocate_auto_memory<ObjectChild2>(controller.get_memory_pool(), std::string("Deallocating ObjectChild2 object"));
    return std::shared_ptr<ObjectChild2>(new (mem.first) ObjectChild2(name), [mem](auto p) { mem.second(); });
}

auto create_child3(Controller& controller, std::string name) {
    auto mem = allocate_auto_memory<ObjectChild3>(controller.get_memory_pool(), std::string("Deallocating ObjectChild3 object"));
    return std::shared_ptr<ObjectChild3>(new (mem.first) ObjectChild3(name), [mem](auto p) { mem.second(); });
}
