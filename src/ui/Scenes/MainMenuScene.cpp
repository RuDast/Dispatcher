#include "MainMenuScene.h"
#include "../../utils/Button.h"
#include <iostream>

using namespace sf;
using namespace std;

MainMenuScene::MainMenuScene() {
    font.loadFromFile("../src/resources/font/main_font.ttf");
    btns_.push_back(Button({250, 120},
                           {345, 282},
                           "LEVEL 1",
                           font,
                           [this]() {
                               if (rating_button_callback_) rating_button_callback_();
                           }));
    btns_.push_back(Button({250, 120}, {605, 282}, "LEVEL 2", font, [this]() { this->print(); }));
    btns_.push_back(Button({250, 120}, {475, 412}, "LEVEL 3", font, [this]() { this->print(); }));
    btns_.push_back(Button({200, 100}, {990, 580}, "UNDEF", font, [this]() { this->print(); }));
    btns_.push_back(Button({200, 100}, {990, 470}, "UNDEF", font, [this]() { this->print(); }));
    btns_.push_back(Button({200, 100}, {990, 20}, "UNDEF", font, [this]() { this->print(); }));
}

void MainMenuScene::setRatBtnCallback(const std::function<void()> &callback) {
    rating_button_callback_ = callback;
}

void MainMenuScene::render(RenderWindow &window) {
    for (auto &btn: btns_) {
        window.draw(btn);
    }
}

void MainMenuScene::handleInput(RenderWindow &window, const Event &event) {
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
