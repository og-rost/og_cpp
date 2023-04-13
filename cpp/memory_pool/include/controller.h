#pragma once

#include "types.h"
#include "tracking_memory_pool.h"

#include <iostream>

class Controller {
public:
    Controller() : m_memoryResource(std::make_shared<MemoryResource_t>(std::pmr::new_delete_resource())),
                   m_memoryPool(std::make_shared<MemoryPool_t>(m_memoryResource.get())) {}

    ~Controller() {
        std::cout << "Memory requested from pool: " << m_memoryPool->GetRequestedSize() << std::endl;
        std::cout << "Memory allocated by pool: " << m_memoryResource->GetAllocatedSize() << std::endl;

        auto objectCounter = m_memoryPool->GetObjectCounter();

        size_t totalObjects = 0;

        for (auto objectInfo : objectCounter) {
            totalObjects += objectInfo.second;
            std::cout << "Number of " + objectInfo.first + " objects allocated: " << objectInfo.second << std::endl;
        }

        std::cout << "Total number of object allocated: " << totalObjects << std::endl;
    }

    MemoryPoolPtr_t get_memory_pool() {
        return m_memoryPool;
    }
private:
    MemoryResourcePtr_t m_memoryResource;
    MemoryPoolPtr_t m_memoryPool;
};
