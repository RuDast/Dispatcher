#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Process.h"
#include "ResourcePool.h"
#include "structures.h"


class Level {
public:
    Level(const LevelConfig& level_config);

private:
    LevelConfig config_; // +
    std::vector<ResourcePool> resources_; // +
    std::vector<Process> processes_; // +

    bool activeRequest = false; // +
    uint64_t id_last_process_ = -1; // +
    ResourceType last_res_type_; // +
    uint64_t last_res_max_count_ = 0; // +

    bool is_complete_ = false;
    bool is_failed = false;

public:
    void generateRequest();

    void draw(sf::RenderWindow& win, const sf::Font& font) const;

    bool checkSafety() const;

    void releaseProcess(uint64_t index);

    int findProcessIndexByPid(uint64_t id) const;

    void handlePlayerChoice(bool grant);

    uint64_t getLastPid() const;

    ResourceType getLastType() const;

    uint64_t getLastAmount() const;

    bool hasActiveRequest() const;

    bool isCompleted() const;

    bool isFailed() const;

    uint64_t getProcessCount() const;
};



#endif //LEVEL_H
