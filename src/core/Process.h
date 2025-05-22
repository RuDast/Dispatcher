#ifndef PROCESS_H
#define PROCESS_H
#include <cstdint>
#include <vector>


class Process {
public:
    Process(uint64_t id,
        const std::vector<uint64_t>& res_max_count);

private:
    uint64_t id_;
    std::vector<uint64_t> resources_max_count_;
    std::vector<uint64_t> resources_current_count_;
    std::vector<uint64_t> resources_needed_count_;

public:
    [[nodiscard]] uint64_t get_id() const;
    [[nodiscard]] const std::vector<uint64_t>& get_res_max_cnt() const;
    [[nodiscard]] const std::vector<uint64_t>& get_res_cur_cnt() const;
    [[nodiscard]] const std::vector<uint64_t>& get_res_ned_cnt() const;

    void pretendAllocate(uint64_t res, uint64_t k);
    void rollbackAllocate(uint64_t res, uint64_t k);

    bool isFinished() const;
    std::vector<uint64_t> realiseAll();
};



#endif //PROCESS_H
