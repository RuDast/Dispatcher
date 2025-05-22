#include "MainMenuScene.h"
#include "../../utils/Button.h"
#include <iostream>

using namespace sf;
using namespace std;

MainMenuScene::MainMenuScene() {
    font.loadFromFile("../src/resources/font/main_font.ttf");

    background_.setSize(Vector2f(1280, 720));
    background_.setFillColor(Color(255, 0, 0));

    btns_.push_back(Button({250, 120},
                           {345, 282},
                           "LEVEL 1",
                           font,
                           [this]() {
                               if (levelSelectCallback_) levelSelectCallback_(1);
                           }));
    btns_.push_back(Button({250, 120},
                           {605, 282},
                           "LEVEL 2",
                           font,
                           [this]() {
                               if (levelSelectCallback_) levelSelectCallback_(2);
                           }));
    btns_.push_back(Button({250, 120},
                           {475, 412},
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
    btns_.push_back(Button({200, 100}, {990, 20}, "settings", font, [this]() {
        if (settings_button_callback_) settings_button_callback_();
    }));
}


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

void MainMenuScene::render(RenderWindow &window) {
    window.draw(background_);

    for (auto &btn: btns_) {
        window.draw(btn);
    }
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
    btns_.clear();
    btns_.push_back(Button({250, 120},
                           {345, 282},
                           "LEVEL 1",
                           font,
                           [this]() {
                               if (levelSelectCallback_) levelSelectCallback_(1);
                           }));
    btns_.push_back(Button({250, 120},
                           {605, 282},
                           "LEVEL 2",
                           font,
                           [this]() {
                               if (levelSelectCallback_) levelSelectCallback_(2);
                           }));
    btns_.push_back(Button({250, 120},
                           {475, 412},
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
    btns_.push_back(Button({200, 100}, {990, 20}, "settings", font, [this]() {
        if (settings_button_callback_) settings_button_callback_();
    }));
}
