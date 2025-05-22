#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <memory>

#include "../Scene.h"
#include "../../core/Level.h"
#include "../../core/structures.h"
#include "../../utils/Button.h"
#include <string>


class GameScene : public Scene {
    unsigned timer = 0;
    float accumulatedTime = 0.0f;
    sf::RenderWindow& window_;
    LevelConfig level_config_;
    std::unique_ptr<Level> level_;
    std::vector<Button> btns_;
    sf::Font font_;
    int            lastPid = -1;
    ResourceType   lastType;
    int            lastAmount = 0;
    sf::Text timerText;
    std::function<void()> back_btn_callback_;
public:
    GameScene(sf::RenderWindow &window, const LevelConfig& config);

    void setBackBtnCallback(const std::function<void()>& callback);
    void handleInput(const sf::Event &event) override;

    void update(float deltaTime) override;

    void render(sf::RenderWindow &window) override;

    bool isComplete() const;

    static void print();

    bool isFailed() const;
};



#endif //GAMESCENE_H
