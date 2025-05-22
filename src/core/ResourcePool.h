#ifndef RESOURCEPOOL_H
#define RESOURCEPOOL_H
#include "structures.h"


class ResourcePool {
public:
    ResourcePool(ResourceType type,
        uint64_t max_count);

private:
    ResourceType type_;
    uint64_t max_count_;
    uint64_t current_count_;

public:
    [[nodiscard]] ResourceType get_type() const;
    [[nodiscard]] uint64_t get_max_count() const;
    [[nodiscard]] uint64_t get_current_count() const;

    bool allocate(uint64_t k);
    void release(uint64_t k);

};



#endif //RESOURCEPOOL_H
