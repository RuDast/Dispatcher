#include "Level.h"

#include <iostream>
#include <random>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>


using namespace sf;
using namespace std;

Level::Level(const LevelConfig &level_config) : config_(level_config),
                                                last_res_type_(ResourceType::Type1),
                                                activeRequest(false), is_complete_(false),
                                                is_failed(false) {
    for (auto &[type, max_count_]: config_.resources_) {
        resources_.emplace_back(type, max_count_);
    }

    for (auto &[id_, max_res_count_]: config_.processes_) {
        processes_.emplace_back(id_, max_res_count_);
    }
}

void Level::generateRequest() {
    std::cout << "[Level] [Begin] generateRequest(): is_complete_="
            << is_complete_ << ", is_failed=" << is_failed
            << ", activeRequest=" << activeRequest << std::endl;
    if (activeRequest || is_complete_ || is_failed) {
        return;
    }

    std::vector<int> procs;
    for (int i = 0; i < (int) processes_.size(); ++i) {
        if (!processes_[i].isFinished())
            procs.push_back(i);
    }

    if (procs.empty()) {
        is_complete_ = true;
        return;
    }

    int pidx = procs[std::rand() % procs.size()];
    id_last_process_ = processes_[pidx].get_id();

    const auto &need = processes_[pidx].get_res_ned_cnt();
    std::vector<int> ress;
    for (int j = 0; j < (int) need.size(); ++j) {
        if (need[j] > 0 && resources_[j].get_current_count() > 0) {
            ress.push_back(j);
        }
    }

    if (ress.empty()) {
        is_complete_ = true;
        return;
    }

    int ridx = ress[std::rand() % ress.size()];
    last_res_type_ = static_cast<ResourceType>(ridx);

    uint64_t available = resources_[ridx].get_current_count();
    uint64_t maxK = std::min<uint64_t>(need[ridx], available);
    last_res_max_count_ = (std::rand() % maxK) + 1;
    activeRequest = true;

    std::cout << "[Level] [End] generateRequest(): is_complete_="
            << is_complete_ << ", is_failed=" << is_failed
            << ", activeRequest=" << activeRequest << std::endl;
}

void Level::draw(RenderWindow &win, const Font &font) const {

    float CELL_WIDTH = 150.f;
    float ORIGIN_Y = 50.f;
    resources_.size() == 5 ? CELL_WIDTH = 100.f: ORIGIN_Y = 150.f;
    const float ORIGIN_X = (1200 - CELL_WIDTH*(resources_.size()+1))/2.0f;
    constexpr float CELL_HEIGHT = 40.f;
    const Color GRID_COLOR(200, 200, 200);
    const Color TEXT_COLOR(50, 50, 50);

    size_t R = resources_.size();
    size_t P = processes_.size(); {
        Text header("PID", font, 16);
        header.setFillColor(TEXT_COLOR);
        header.setPosition(ORIGIN_X + 5, ORIGIN_Y - CELL_HEIGHT + 5);
        win.draw(header);
    }

    for (size_t j = 0; j < R; ++j) {
        Text hdr;
        hdr.setFont(font);
        hdr.setCharacterSize(16);
        hdr.setFillColor(TEXT_COLOR);
        hdr.setString("R" + std::to_string(j + 1));
        hdr.setPosition(ORIGIN_X + (j + 1) * CELL_WIDTH + 5, ORIGIN_Y - CELL_HEIGHT + 5);
        win.draw(hdr);
    }

    for (size_t i = 0; i < P; ++i) {
        float y = ORIGIN_Y + i * CELL_HEIGHT;

        RectangleShape pidCell({CELL_WIDTH, CELL_HEIGHT});
        pidCell.setPosition(ORIGIN_X, y);
        pidCell.setFillColor(sf::Color::Transparent);
        pidCell.setOutlineColor(GRID_COLOR);
        pidCell.setOutlineThickness(1.f);
        win.draw(pidCell);

        Text pidText;
        pidText.setFont(font);
        pidText.setCharacterSize(14);
        pidText.setFillColor(TEXT_COLOR);
        pidText.setString(std::to_string(processes_[i].get_id()));
        pidText.setPosition(ORIGIN_X + 5, y + 5);
        win.draw(pidText);

        auto alloc = processes_[i].get_res_cur_cnt();
        auto need = processes_[i].get_res_ned_cnt();
        for (size_t j = 0; j < R; ++j) {
            float x = ORIGIN_X + (j + 1) * CELL_WIDTH;

            RectangleShape cell({CELL_WIDTH, CELL_HEIGHT});
            cell.setPosition(x, y);
            cell.setFillColor(sf::Color::Transparent);
            cell.setOutlineColor(GRID_COLOR);
            cell.setOutlineThickness(1.f);
            win.draw(cell);

            Text txt;
            txt.setFont(font);
            txt.setCharacterSize(14);
            txt.setFillColor(TEXT_COLOR);
            txt.setString(std::to_string(alloc[j]) + " / " + std::to_string(need[j]));

            FloatRect b = txt.getLocalBounds();
            float tx = x + (CELL_WIDTH - b.width) / 2 - b.left;
            float ty = y + (CELL_HEIGHT - b.height) / 2 - b.top;
            txt.setPosition(tx, ty);
            win.draw(txt);
        }
    } {
        float y = ORIGIN_Y + P * CELL_HEIGHT;

        RectangleShape labelCell({CELL_WIDTH, CELL_HEIGHT});
        labelCell.setPosition(ORIGIN_X, y);
        labelCell.setFillColor(sf::Color::Transparent);
        labelCell.setOutlineColor(GRID_COLOR);
        labelCell.setOutlineThickness(1.f);
        win.draw(labelCell);

        Text lbl("Available", font, 14);
        lbl.setFillColor(TEXT_COLOR);
        lbl.setPosition(ORIGIN_X + 5, y + 5);
        win.draw(lbl);

        for (size_t j = 0; j < R; ++j) {
            float x = ORIGIN_X + (j + 1) * CELL_WIDTH;

            RectangleShape cell({CELL_WIDTH, CELL_HEIGHT});
            cell.setPosition(x, y);
            cell.setFillColor(sf::Color::Transparent);
            cell.setOutlineColor(GRID_COLOR);
            cell.setOutlineThickness(1.f);
            win.draw(cell);

            Text avaText;
            avaText.setFont(font);
            avaText.setCharacterSize(14);
            avaText.setFillColor(TEXT_COLOR);
            avaText.setString(std::to_string(resources_[j].get_current_count()));

            FloatRect b = avaText.getLocalBounds();
            float tx = x + (CELL_WIDTH - b.width) / 2 - b.left;
            float ty = y + (CELL_HEIGHT - b.height) / 2 - b.top;
            avaText.setPosition(tx, ty);
            win.draw(avaText);
        }
    }
}

bool Level::checkSafety() const {
    const int R = resources_.size();
    const int P = processes_.size();

    std::vector<int> work(R);
    for (int j = 0; j < R; ++j)
        work[j] = resources_[j].get_current_count();

    std::vector<bool> finish(P);
    for (int i = 0; i < P; ++i)
        finish[i] = processes_[i].isFinished();

    bool changed;
    do {
        changed = false;
        for (int i = 0; i < P; ++i) {
            if (!finish[i]) {
                const auto &need = processes_[i].get_res_ned_cnt();
                bool canFinish = true;
                for (int j = 0; j < R; ++j)
                    if (need[j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                if (canFinish) {
                    const auto &alloc = processes_[i].get_res_cur_cnt();
                    for (int j = 0; j < R; ++j)
                        work[j] += alloc[j];
                    finish[i] = true;
                    changed = true;
                }
            }
        }
    } while (changed);

    return std::all_of(finish.begin(), finish.end(), [](bool f) { return f; });
}

void Level::releaseProcess(const uint64_t index) {
    const auto released = processes_[index].realiseAll();
    for (size_t j = 0; j < resources_.size(); ++j)
        resources_[j].release(released[j]);
}

int Level::findProcessIndexByPid(const uint64_t id) const {
    for (int i = 0; i < static_cast<int>(processes_.size()); ++i) {
        if (processes_[i].get_id() == id)
            return i;
    }
    return -1;
}

void Level::handlePlayerChoice(const bool grant) {
    if (!activeRequest || is_complete_ || is_failed) return;

    int pi = findProcessIndexByPid(id_last_process_);
    int r = static_cast<int>(last_res_type_);
    int k = last_res_max_count_;

    if (grant) {
        // формальная проверка
        if (k > resources_[r].get_current_count() || k > processes_[pi].get_res_ned_cnt()[r]) {
            is_failed = true;
        } else {
            // 1) притворно выдаём
            resources_[r].allocate(k);
            processes_[pi].pretendAllocate(r,k);

            // 2) если процесс завершился — виртуально освобождаем
            bool justFinished = processes_[pi].isFinished();
            std::vector<uint64_t> released;
            if (justFinished) {
                released = processes_[pi].realiseAll();
                for (int j = 0; j < resources_.size(); ++j)
                    resources_[j].release(released[j]);
            }

            // 3) safety-check на этом состоянии
            if (!checkSafety()) {
                // откатываем всё
                if (justFinished) {
                    // надо вернуть allocation обратно в процесс
                    processes_[pi].pretendAllocate(r,k);
                    // и здесь _вручную_ убрать только что вернувшиеся в пул ресурсы:
                    for (int j = 0; j < resources_.size(); ++j)
                        resources_[j].allocate(released[j]);
                }
                processes_[pi].rollbackAllocate(r,k);
                resources_[r].release(k);
                is_failed = true;
            }
            // иначе «закрепляем» — ничего не делаем, всё уже в ресурсах
        }
    }
    // else { // отказ
    //     // симулируем выдачу
    //     resources_[r].allocate(k);
    //     processes_[pi].pretendAllocate(r, k);
    //
    //     bool safe = checkSafety();
    //
    //     // откатываем
    //     processes_[pi].rollbackAllocate(r, k);
    //     resources_[r].release(k);
    //
    //     // если было безопасно — игрок ошибся (failure), иначе отказ правильный
    //     if (safe) is_failed = true;
    // }
    activeRequest = false;

    bool allDone = true;
    for (auto &p: processes_)
        if (!p.isFinished()) {
            allDone = false;
            break;
        }
    if (allDone)
        is_complete_ = true;
}

uint64_t Level::getLastPid() const {
    return id_last_process_;
}

ResourceType Level::getLastType() const {
    return last_res_type_;
}

uint64_t Level::getLastAmount() const {
    return last_res_max_count_;
}

bool Level::hasActiveRequest() const {
    return activeRequest;
}

bool Level::isCompleted() const {
    for (const auto &proc: processes_) {
        if (!proc.isFinished()) return false;
    }
    return true;
}

bool Level::isFailed() const {
    return is_failed;
}

uint64_t Level::getProcessCount() const {
    return processes_.size();
}
