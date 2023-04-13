#pragma once

#include <memory_resource>
#include <unordered_map>

class TrackingMemoryPool : public std::pmr::synchronized_pool_resource {
public:
    TrackingMemoryPool() : std::pmr::synchronized_pool_resource() {}
    TrackingMemoryPool(std::pmr::memory_resource* upstream) : std::pmr::synchronized_pool_resource(upstream) {}
protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        if ((m_curr += bytes) > m_max) {
            m_max = m_curr;
        }
        return std::pmr::synchronized_pool_resource::do_allocate(bytes, alignment);
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        m_curr -= bytes;
        std::pmr::synchronized_pool_resource::do_deallocate(p, bytes, alignment);
    }
public:
    size_t GetRequestedSize() {
        return m_max;
    }

    void AddToObjectCounter(const std::string& objectName) {
        ++m_objectCounter[objectName];
    }

    std::unordered_map<std::string, size_t> GetObjectCounter() {
        return m_objectCounter;
    }
private:
    size_t m_max = 0;
    size_t m_curr = 0;
    std::unordered_map<std::string, size_t> m_objectCounter; 
};

class TrackingMemoryResource : public std::pmr::memory_resource {
public:
    TrackingMemoryResource(std::pmr::memory_resource* upstream) : m_upstream(upstream) {}

    void* do_allocate(std::size_t bytes, std::size_t alignment) override  {
        if ((m_curr += bytes) > m_capacity) {
            m_capacity = m_curr;
        }
        return m_upstream->allocate(bytes, alignment);
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override  {
        m_curr -= bytes;
        m_upstream->deallocate(p, bytes, alignment);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override  {
        return m_upstream->is_equal(other);
    }

    size_t GetAllocatedSize() {
        return m_capacity;
    }
private:
    std::pmr::memory_resource* m_upstream;
    size_t m_capacity = 0;
    size_t m_curr = 0;
};

