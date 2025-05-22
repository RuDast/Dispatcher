#include "RatingScene.h"

#include <iostream>

using namespace sf;
using namespace std;

RatingScene::RatingScene() {
    font.loadFromFile("../src/resources/font/main_font.ttf");
    btns_.push_back(Button({250, 120},
                           {50, 50},
                           "Back",
                           font,
                           [this]() {
                               if (back_btn_callback_) back_btn_callback_();
                           }));
}

void RatingScene::setBackBtnCallback(const std::function<void()> &callback) {
    back_btn_callback_ = callback;
}

void RatingScene::handleInput(const Event &event) {
    for (auto &btn: btns_) {
        btn.handleEvent(event);
    }
}

void RatingScene::update(float deltaTime) {
    // cerr << "[DEBUG] RatingScene::update();" << endl;
}

void RatingScene::render(RenderWindow &window) {
    for (auto &btn: btns_) {
        window.draw(btn);
    }
}
