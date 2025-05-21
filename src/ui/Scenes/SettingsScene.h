#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H
#include "../Scene.h"


class SettingsScene : public Scene {
public:
    void handleInput(sf::RenderWindow &window, const sf::Event &event) override;

    void update(float deltaTime) override;

    void render(sf::RenderWindow &window) override;
};


#endif //SETTINGSSCENE_H
