#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "Scenes/MainMenuScene.h"


class Game {
    sf::RenderWindow window_;
    MainMenuScene mainMenuScene;
    Scene *current_scene_ = nullptr;

public:
    Game();
    void run();

    void processEvents();
    // void update(float dt);
    void render();

};



#endif //GAME_H
