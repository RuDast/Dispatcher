#include "FAQScene.h"
#include <iostream>

using namespace sf;
using namespace std;

FAQScene::FAQScene()
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

void FAQScene::setBackBtnCallback(const std::function<void()> &callback)
{
    back_btn_callback_ = callback;
}


void FAQScene::handleInput(RenderWindow &window, const Event &event) {
    for (auto &btn: btns_) {
        btn.handleEvent(event);
    }
}

void FAQScene::update(float deltaTime) {
    //cerr << "[DEBUG] SettingsScene::update();" << endl;
}

void FAQScene::render(RenderWindow &window) {
    for (auto &btn: btns_) {
        window.draw(btn);
    }
}