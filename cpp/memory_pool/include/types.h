#pragma once

#include <memory>
#include <memory_resource>

class TrackingMemoryResource;
class TrackingMemoryPool;

using MemoryResource_t = TrackingMemoryResource;
using MemoryPool_t = TrackingMemoryPool;

using MemoryResourcePtr_t = std::shared_ptr<MemoryResource_t>;
using MemoryPoolPtr_t = std::shared_ptr<MemoryPool_t>;
