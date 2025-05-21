#include "GameScene.h"

#include <iostream>

using namespace sf;
using namespace std;

GameScene::GameScene(RenderWindow &window, const LevelConfig &config) : window_(window),
                                                                        level_config_(config),
                                                                        level_(config) {
    font_.loadFromFile("../src/resources/font/main_font.ttf");
    btns_.push_back(Button({250, 120}, {605, 282}, "Give", font_, [this]() { this->print(); }));
    btns_.push_back(Button({250, 120}, {475, 412}, "Cancel", font_, [this]() { this->print(); }));
}

void GameScene::handleInput(RenderWindow &window, const Event &event) {
    for (auto &btn: btns_) {
        btn.handleEvent(event);
    }

}

void GameScene::update(float deltaTime) {
}

void GameScene::render(RenderWindow &window) {
    for (auto &btn: btns_) {
        window.draw(btn);
    }
}

void GameScene::print() {
    cerr << "[TEST] Button pressed." << endl;
}
