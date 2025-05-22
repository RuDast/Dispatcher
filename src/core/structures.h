#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <cstdint>
#include <vector>

enum class ResourceType {
    Type1 = 0,
    Type2 = 1,
    Type3 = 2,
    Type4 = 3,
    Type5 = 4
};

struct ResourcePoolConfig {
    ResourceType type;
    uint64_t max_count_;
};

struct ProcessConfig {
    uint64_t id_;
    std::vector<uint64_t> max_res_count_;
};

struct LevelConfig {
    std::vector<ResourcePoolConfig> resources_;
    std::vector<ProcessConfig> processes_;
};

#endif //STRUCTURES_H
