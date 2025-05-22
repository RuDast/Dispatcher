#include "SettingsScene.h"

#include <iostream>

using namespace sf;
using namespace std;

SettingsScene::SettingsScene()
{
    font.loadFromFile("../src/resources/font/main_font.ttf");
    btns_.push_back(Button({250, 120},
                           {50, 50},
                           "Back",
                           font,
                           [this]() {
                               if (back_btn_callback_) back_btn_callback_();
                           }));
}

void SettingsScene::setBackBtnCallback(const std::function<void()> &callback)
{
    back_btn_callback_ = callback;
}


void SettingsScene::handleInput(const Event &event) {
    for (auto &btn: btns_) {
        btn.handleEvent(event);
    }
}

void SettingsScene::update(float deltaTime) {
    //cerr << "[DEBUG] SettingsScene::update();" << endl;
}

void SettingsScene::render(RenderWindow &window) {
    for (auto &btn: btns_) {
        window.draw(btn);
    }
}
