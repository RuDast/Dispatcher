#include "SettingsScene.h"
#include <iostream>
#include "Rating.h"
using namespace sf;
using namespace std;

SettingsScene::SettingsScene() : savedNickname("Player"), currentNickname("Player")
{
    if (!font.loadFromFile("../src/resources/font/main_font.ttf")) {
        cerr << "Error loading font" << endl;
    }

    // Кнопка назад
    btns_.push_back(Button({250, 120}, {50, 50}, "Back", font, [this]() {
        resetNotification();
        if (back_btn_callback_) back_btn_callback_();
    }));

    // Кнопка сохранения
    btns_.push_back(Button({200, 50}, {150, 300}, "Save", font, [this]() {
    if (!currentNickname.empty()) {
        savedNickname = currentNickname;
        if (Rating::isNicknameExists(savedNickname)) {
            notificationText.setString("Successful authorization!");
            notificationText.setPosition(120, 270); // Подправляем позицию для нового текста
        } else {
            Rating::saveNickname(savedNickname);
            notificationText.setString("Nickname saved!");
            notificationText.setPosition(150, 270);
        }
        showNotification = true;
        notificationTimer = 2.0f;
    }
}));

    // Поле ввода никнейма
    nicknameBox.setSize({300, 50});
    nicknameBox.setPosition({100, 200});
    nicknameBox.setFillColor(Color::White);
    nicknameBox.setOutlineThickness(2);
    nicknameBox.setOutlineColor(Color::Black);

    nicknameText.setFont(font);
    nicknameText.setCharacterSize(24);
    nicknameText.setFillColor(Color::Black);
    nicknameText.setPosition({110, 210});
    nicknameText.setString(currentNickname);

    // Настройка уведомления
    notificationText.setFont(font);
    notificationText.setCharacterSize(20);
    notificationText.setFillColor(Color::Green);
    notificationText.setString("Nickname saved!"); // По умолчанию
    notificationText.setPosition(150, 270);
    notificationText.setStyle(Text::Bold);

}

void SettingsScene::resetNotification() {
    showNotification = false;
    notificationTimer = 0.f;
}

void SettingsScene::handleInput(const sf::Event &event) {
    cout << "Test" << endl;
}

void SettingsScene::handleInput(RenderWindow &window, const Event &event) {
    // Обработка кнопок
    for (auto &btn : btns_) {
        btn.handleEvent(event);
    }

    // Обработка ввода никнейма
    if (event.type == Event::MouseButtonPressed) {
        if (nicknameBox.getGlobalBounds().contains(
            window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y}))) {
            isTypingNickname = true;
            nicknameBox.setOutlineColor(Color::Blue);
        } else {
            isTypingNickname = false;
            nicknameBox.setOutlineColor(Color::Black);
        }
    }

    if (event.type == Event::TextEntered && isTypingNickname) {
        if (event.text.unicode == '\b' && !currentNickname.empty()) {
            currentNickname.pop_back();
        } else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\t') {
            if (currentNickname.size() < 15) {
                currentNickname += static_cast<char>(event.text.unicode);
            }
        }
        nicknameText.setString(currentNickname);
    }
}

void SettingsScene::update(float deltaTime) {
    if (showNotification) {
        notificationTimer -= deltaTime;
        if (notificationTimer <= 0.f) {
            resetNotification();
        }
    }
}

void SettingsScene::render(RenderWindow &window) {
    for (auto &btn : btns_) {
        window.draw(btn);
    }

    window.draw(nicknameBox);
    window.draw(nicknameText);

    if (showNotification) {
        window.draw(notificationText);
    }
}

std::string SettingsScene::getNickname() const {
    return savedNickname; // Возвращаем только сохраненный никнейм
}

void SettingsScene::setBackBtnCallback(const std::function<void()> &callback) {
    back_btn_callback_ = callback;
}