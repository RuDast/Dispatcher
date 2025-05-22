#include "GameScene.h"
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

GameScene::GameScene(RenderWindow &window, const LevelConfig &config) : window_(window),
                                                                        level_config_(config),
                                                                        level_(config) {
    font.loadFromFile("../src/resources/font/main_font.ttf");
    btns_.push_back(Button({250, 120}, {605, 282}, "Give", font, [this]() { this->print(); }));
    btns_.push_back(Button({250, 120}, {475, 412}, "Cancel", font, [this]() { this->print(); }));
    btns_.push_back(Button({250, 120}, {50, 50},"Back",font,[this]() {if (back_btn_callback_) {back_btn_callback_(); timer = 0;}}));

    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(100, 300);

}

void GameScene::setBackBtnCallback(const std::function<void()> &callback)
{
    back_btn_callback_ = callback;
}

void GameScene::handleInput(RenderWindow &window, const Event &event) {
    for (auto &btn: btns_) {
        btn.handleEvent(event);
    }

}

void GameScene::update(float deltaTime) {

    accumulatedTime+= deltaTime;
    if(accumulatedTime >= 1.0f)
    {
        timer++;
        accumulatedTime = 0.0f;
        std::stringstream ss;
        ss << "Time: " << timer << "s";
        timerText.setString(ss.str());
    }


}

void GameScene::render(RenderWindow &window)
{
    window.clear();
    window.draw(timerText);
    for (auto &btn: btns_)
        {
        window.draw(btn);
    }
}

void GameScene::print() {
    cerr << "[TEST] Button pressed." << endl;
}
