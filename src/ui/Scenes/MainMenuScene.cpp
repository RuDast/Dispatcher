#include "MainMenuScene.h"

#include <iostream>

using namespace sf;
using namespace std;

MainMenuScene::MainMenuScene() {
    btns_.emplace_back(Vector2f{100, 100});
    btns_[0].setFillColor(Color::Blue); // TODO убрать
}

void MainMenuScene::render(RenderWindow &window) {
    for (auto& btn : btns_) {
        window.draw(btn);
    }
}

void MainMenuScene::handleInput(RenderWindow &window, const Event &event) {
    cerr << "[DEBUG] MainMenuScene::handleInput();" << endl;
}

void MainMenuScene::update(float deltaTime) {
    cerr << "[DEBUG] MainMenuScene::update();" << endl;
}
