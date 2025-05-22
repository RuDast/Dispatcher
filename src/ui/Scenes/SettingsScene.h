#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include "../Scene.h"
#include "../../utils/Button.h"
#include <SFML/Graphics.hpp>

class SettingsScene : public Scene {
public:
    SettingsScene();
    void setBackBtnCallback(const std::function<void()>& callback);
    void handleInput(sf::RenderWindow &window, const sf::Event &event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow &window) override;
    std::string getNickname() const; // Новый метод вместо createNickname

private:
    std::function<void()> back_btn_callback_;
    sf::Font font;
    std::vector<Button> btns_;

    // Для работы с никнеймом
    std::string currentNickname; // Текущий вводимый ник
    std::string savedNickname;   // Сохраненный ник (только после нажатия Save)

    // Элементы для ввода никнейма
    sf::Text nicknameText;
    sf::RectangleShape nicknameBox;
    bool isTypingNickname = false;

    // Для уведомления
    sf::Text notificationText;
    float notificationTimer = 0.f;
    bool showNotification = false;

    void resetNotification();
};

#endif //SETTINGSSCENE_H