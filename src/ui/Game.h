#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "Scenes/GameScene.h"
#include "Scenes/FAQScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/RatingScene.h"
#include "Scenes/SettingsScene.h"

enum class GameStatus {
    None = 0,
    Fail = 1,
    Success = 2,
};


class Game {
    sf::RenderWindow window_;
    MainMenuScene main_menu_scene_;
    RatingScene rating_scene_;
    SettingsScene settings_scene_;
    FAQScene faq_scene_;
    Scene *current_scene_ = nullptr;
    GameScene *game_scene_ = nullptr;

    sf::RectangleShape background;
    bool pendingEnd_ = false;

    bool waitingEnd_ = false;
    float endTimer_ = 0.f;

    float test_timer_ = 0;

    GameStatus game_status_= GameStatus::None;

public:
    Game();

    void run();

    void processEvents();

    void update(float dt);

    void render();

    void switchToRatingScene();

    void switchToSettingsScene();

    void switchToFAQScene();

    void switchToMainScene();

    void startLevel(unsigned level);

    void endLevel();
};


#endif //GAME_H
