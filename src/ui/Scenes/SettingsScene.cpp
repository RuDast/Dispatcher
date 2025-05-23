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
    background_.setSize(Vector2f(1280, 720));
    background_.setFillColor(Color(153, 204, 255));

    // Кнопка назад
    btns_.push_back(Button({250, 120}, {50, 50}, "Back", font, [this]() {
        resetNotification();
        if (back_btn_callback_) back_btn_callback_();
    }));

    // Кнопка сохранения
    btns_.push_back(Button({200, 50}, {480, 400}, "Save", font, [this]() {
    if (!currentNickname.empty()) {
        savedNickname = currentNickname;

        // Проверяем существование игрока
        auto players = Rating::getAllPlayers();
        bool playerExists = false;
        for (const auto& player : players) {
            if (player.first == savedNickname) {
                playerExists = true;
                break;
            }
        }

        if (playerExists) {
            notificationText.setString("Welcome back!");
            notificationText.setPosition(490, 360);
        } else {
            Rating::savePlayer(savedNickname, 0); // Регистрируем нового игрока с 0 очков
            notificationText.setString("Registration complete!");
            notificationText.setPosition(460, 360);
        }

        showNotification = true;
        notificationTimer = 2.0f;
    }
}));
    btns_.push_back(Button({200, 50}, {50, 600}, "Clear Ratings", font, [this]() {
    Rating::clearRatings();
    showClearNotification = true;
    clearNotificationTimer = 2.0f;
}));






    // Поле ввода никнейма
    nicknameBox.setSize({300, 50});
    nicknameBox.setPosition({435, 300});
    nicknameBox.setFillColor(Color::White);
    nicknameBox.setOutlineThickness(2);
    nicknameBox.setOutlineColor(Color::Black);

    nicknameText.setFont(font);
    nicknameText.setCharacterSize(24);
    nicknameText.setFillColor(Color::Black);
    nicknameText.setPosition({435, 310});
    nicknameText.setString(currentNickname);


    // Настройка уведомления
    notificationText.setFont(font);
    notificationText.setCharacterSize(20);
    notificationText.setFillColor(Color::Green);
    notificationText.setString("Nickname saved!"); // По умолчанию
    notificationText.setStyle(Text::Bold);
    notificationText.setString("Ratings cleared!"); // Будем переиспользовать тот же Text
}

void SettingsScene::resetNotification() {
    showNotification = false;
    notificationTimer = 0.f;
}

void SettingsScene::handleInput(const sf::Event &event) {
    cout << "Test" << endl;
}

const std::string & SettingsScene::get_name() const {
    return currentNickname;
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
    if (showClearNotification) {
        clearNotificationTimer -= deltaTime;
        if (clearNotificationTimer <= 0.f) {
            showClearNotification = false;
        }
    }
}

void SettingsScene::render(RenderWindow &window) {
    window.draw(background_);

    for (auto &btn : btns_) {
        window.draw(btn);
    }


    window.draw(nicknameBox);
    window.draw(nicknameText);

    if (showNotification) {
        window.draw(notificationText);
    }
    if (showClearNotification) {
        notificationText.setString("Ratings cleared!");
        notificationText.setPosition(70, 660); // Подправим позицию
        window.draw(notificationText);
    }
}

std::string SettingsScene::getNickname() const {
    return savedNickname; // Возвращаем только сохраненный никнейм
}

void SettingsScene::setBackBtnCallback(const std::function<void()> &callback) {
    back_btn_callback_ = callback;
}