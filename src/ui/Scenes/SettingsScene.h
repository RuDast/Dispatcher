#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H
#include "../Scene.h"
#include "../../utils/Button.h"

class SettingsScene : public Scene {
public:
    SettingsScene();

    void setBackBtnCallback(const std::function<void()>& callback);

    void handleInput(const sf::Event &event) override;

    void update(float deltaTime) override;

    void render(sf::RenderWindow &window) override;
private:
    std::function<void()> back_btn_callback_;
    sf::Font font;
    std::vector<Button> btns_;
};


#endif //SETTINGSSCENE_H
