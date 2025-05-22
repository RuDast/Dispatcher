#include "ResourcePool.h"

ResourcePool::ResourcePool(const ResourceType type, const uint64_t max_count) : type_(type), max_count_(max_count),
    current_count_(max_count) {
}

ResourceType ResourcePool::get_type() const {
    return type_;
}

uint64_t ResourcePool::get_max_count() const {
    return max_count_;
}

uint64_t ResourcePool::get_current_count() const {
    return current_count_;
}

bool ResourcePool::allocate(const uint64_t k) {
    if (current_count_ >= k) {
        current_count_ -= k;
        return true;
    }
    return false;
}

void ResourcePool::release(const uint64_t k) {
    current_count_ += k;
    if (current_count_ > max_count_)
        current_count_ = max_count_;
}
