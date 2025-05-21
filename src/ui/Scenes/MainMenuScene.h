#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H
#include "../Scene.h"
#include "../../utils/Button.h"


class MainMenuScene : public Scene {
public:
    MainMenuScene();

private:
    std::vector<Button> btns_;
    sf::Font font;
    std::function<void()> rating_button_callback_;
public:
    void setRatBtnCallback(const std::function<void()>& callback);

    void render(sf::RenderWindow &window) override;

    void handleInput(sf::RenderWindow &window, const sf::Event &event) override;

    void update(float deltaTime) override;

    void print() const;

};


#endif //MAINMENUSCENE_H
