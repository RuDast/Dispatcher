#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "../Scene.h"
#include "../../core/Level.h"
#include "../../core/structures.h"
#include "../../utils/Button.h"


class GameScene : public Scene {
    sf::RenderWindow& window_;
    LevelConfig level_config_;
    Level level_;
    std::vector<Button> btns_;
    sf::Font font;
    std::function<void()> back_btn_callback_;
public:
    GameScene(sf::RenderWindow &window, const LevelConfig& config);

    void setBackBtnCallback(const std::function<void()>& callback);

    void handleInput(sf::RenderWindow &window, const sf::Event &event) override;

    void update(float deltaTime) override;

    void render(sf::RenderWindow &window) override;

    void print();
};



#endif //GAMESCENE_H
