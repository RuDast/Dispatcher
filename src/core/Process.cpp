#include "Process.h"
#include <algorithm>

using namespace std;

Process::Process(uint64_t id, const vector<uint64_t> &res_max_count) : id_(id),
                                                                            resources_max_count_(res_max_count),
                                                                            resources_current_count_(
                                                                                res_max_count.size(), 0),
                                                                            resources_needed_count_(res_max_count) {
}

uint64_t Process::get_id() const {
    return id_;
}

const vector<uint64_t> & Process::get_res_max_cnt() const {
    return resources_max_count_;
}

const vector<uint64_t> & Process::get_res_cur_cnt() const {
    return resources_current_count_;
}

const vector<uint64_t> & Process::get_res_ned_cnt() const {
    return resources_needed_count_;
}

void Process::pretendAllocate(const uint64_t res, const uint64_t k) {
    resources_current_count_[res] += k;
    resources_needed_count_[res] -= k;
}

void Process::rollbackAllocate(const uint64_t res, const uint64_t k) {
    resources_current_count_[res] -= k;
    resources_needed_count_[res] += k;
}

bool Process::isFinished() const {
    for (const uint64_t res : resources_needed_count_) {
        if (res > 0)
            return false;
    }
    return true;
}

vector<uint64_t> Process::realiseAll() {
    auto ret = resources_current_count_;
    fill(resources_current_count_.begin(), resources_current_count_.end(), 0);

    return ret;
}
