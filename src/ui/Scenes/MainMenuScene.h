#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H
#include "../Scene.h"


class MainMenuScene : public Scene {
public:
    MainMenuScene();
private:
    std::vector<sf::RectangleShape> btns_; // TODO поменять на button
public:
    void render(sf::RenderWindow &window) override;

    void handleInput(sf::RenderWindow &window, const sf::Event &event) override;

    void update(float deltaTime) override;
};



#endif //MAINMENUSCENE_H
