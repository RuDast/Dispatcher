#include "RatingScene.h"

#include <iostream>

using namespace sf;
using namespace std;

RatingScene::RatingScene() : test_({100, 100}) {
    test_.setFillColor(Color::Red);
}

void RatingScene::handleInput(RenderWindow &window, const Event &event) {
    cerr << "[DEBUG] RatingScene::handleInput();" << endl;
}

void RatingScene::update(float deltaTime) {
    cerr << "[DEBUG] RatingScene::update();" << endl;
}

void RatingScene::render(RenderWindow &window) {
    window.draw(test_);
}
