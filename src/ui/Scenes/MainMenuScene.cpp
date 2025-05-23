#include "MainMenuScene.h"
#include "../../utils/Button.h"
#include <iostream>

using namespace sf;
using namespace std;

MainMenuScene::MainMenuScene() {
    font.loadFromFile("../src/resources/font/main_font.ttf");

    // Настройка фона
    background_.setSize(Vector2f(1280, 720));
    background_.setFillColor(Color(153, 204, 255));

    // Настройка заголовка игры
    gameTitle_.setFont(font);
    gameTitle_.setString("DISPATCHER GAME");
    gameTitle_.setCharacterSize(80); // Большой размер шрифта
    gameTitle_.setFillColor(Color::Black);
    gameTitle_.setStyle(Text::Bold);

    // Центрирование заголовка по горизонтали и размещение выше кнопок
    FloatRect titleRect = gameTitle_.getLocalBounds();
    gameTitle_.setOrigin(titleRect.left + titleRect.width/2.0f,
                        titleRect.top + titleRect.height/2.0f);
    gameTitle_.setPosition(Vector2f(1200/2.0f, 150));

    // Настройка кнопок (сдвинуты ниже, чтобы не перекрывались с заголовком)
    const float levelBtnYBase = 350;
    btns_.push_back(Button({250, 80},
                           {350, levelBtnYBase},
                           "LEVEL 1",
                           font,
                           [this]() { if (levelSelectCallback_) levelSelectCallback_(1); }));

    btns_.push_back(Button({250, 80},
                           {600, levelBtnYBase},
                           "LEVEL 2",
                           font,
                           [this]() { if (levelSelectCallback_) levelSelectCallback_(2); }));

    btns_.push_back(Button({250, 80},
                           {475, levelBtnYBase + 130},
                           "LEVEL 3",
                           font,
                           [this]() { if (levelSelectCallback_) levelSelectCallback_(3); }));

    // Настройка боковых кнопок

    btns_.push_back(Button({200, 100}, {990, 580}, "rating", font, [this]() {
        if (rating_button_callback_) rating_button_callback_();
    }));
    btns_.push_back(Button({200, 100}, {990, 470}, "FAQ", font,
                           [this]() { if (faq_button_callback_) faq_button_callback_(); }));
    btns_.push_back(Button({200, 100}, {20, 580}, "settings", font, [this]() {
        if (settings_button_callback_) settings_button_callback_();
    }));
}


void MainMenuScene::render(RenderWindow &window) {
    window.draw(background_);
    window.draw(gameTitle_); // Рисуем заголовок

    for (auto &btn: btns_) {
        window.draw(btn);
    }
}

// Остальные методы остаются без изменений
void MainMenuScene::setRatingBtnCallback(const std::function<void()> &callback) {
    rating_button_callback_ = callback;
}

void MainMenuScene::setLevSelCallback(const std::function<void(int)> &callback) {
    levelSelectCallback_ = callback;
}

void MainMenuScene::setLvl1BtnCallback(const std::function<void()> &callback) {
    lvl1_button_callback_ = callback;
}

void MainMenuScene::setSettingsBtnCallback(const std::function<void()> &callback) {
    settings_button_callback_ = callback;
}

void MainMenuScene::setFAQBtnCallback(const std::function<void()> &callback) {
    faq_button_callback_ = callback;
}

void MainMenuScene::handleInput(const Event &event) {
    for (auto &btn: btns_) {
        btn.handleEvent(event);
    }
}

void MainMenuScene::update(float deltaTime) {
    // cerr << "[DEBUG] MainMenuScene::update();" << endl;
}

void MainMenuScene::print() const {
    cerr << "[TEST] Button pressed." << endl;
}

void MainMenuScene::reset() {
    font.loadFromFile("../src/resources/font/main_font.ttf");

    // Восстановление заголовка
    gameTitle_.setFont(font);

    btns_.clear();
    btns_.push_back(Button({250, 120},
                           {345, 282 + 40},
                           "LEVEL 1",
                           font,
                           [this]() {
                               if (levelSelectCallback_) levelSelectCallback_(1);
                           }));
    btns_.push_back(Button({250, 120},
                           {605, 282 + 40},
                           "LEVEL 2",
                           font,
                           [this]() {
                               if (levelSelectCallback_) levelSelectCallback_(2);
                           }));
    btns_.push_back(Button({250, 120},
                           {475, 412 + 40},
                           "LEVEL 3",
                           font,
                           [this]() {
                               if (levelSelectCallback_) levelSelectCallback_(3);
                           }));
    btns_.push_back(Button({200, 100}, {990, 580}, "rating", font, [this]() {
        if (rating_button_callback_) rating_button_callback_();
    }));
    btns_.push_back(Button({200, 100}, {990, 470}, "FAQ", font,
                           [this]() { if (faq_button_callback_) faq_button_callback_(); }));
    btns_.push_back(Button({200, 100}, {20, 580}, "settings", font, [this]() {
        if (settings_button_callback_) settings_button_callback_();
    }));
}