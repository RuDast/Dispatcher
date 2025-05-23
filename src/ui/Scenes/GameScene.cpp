#include "GameScene.h"
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

GameScene::GameScene(RenderWindow &window, const LevelConfig &config) : window_(window),
                                                                        level_config_(config) {
    background_.setSize(Vector2f(1280, 720));
    background_.setFillColor(Color(153, 204, 255));

    font_.loadFromFile("../src/resources/font/main_font.ttf");
    level_ = make_unique<Level>(level_config_);
    btns_.push_back(Button({250, 120},
                           {600, 550},
                           "Give",
                           font_,
                           [this]() { level_->handlePlayerChoice(true); }));
    btns_.push_back(Button({250, 120},
                           {340, 550},
                           "Cancel",
                           font_,
                           [this]() { level_->handlePlayerChoice(false); }));
    btns_.push_back(Button({200, 100}, {25, 25},"Back",font_,[this]() {if (back_btn_callback_) {back_btn_callback_(); timer = 0;}}));

    timerText.setFont(font_);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(1020, 50);
}

void GameScene::setBackBtnCallback(const std::function<void()> &callback)
{
    back_btn_callback_ = callback;
}

void GameScene::handleInput(const Event &event) {
    for (auto &btn: btns_) {
        btn.handleEvent(event);
    }
}

void GameScene::update(float deltaTime) {
    if (!level_->hasActiveRequest() &&
        !level_->isCompleted() &&
        !level_->isFailed()) {
        level_->generateRequest();

        lastPid = level_->getLastPid();
        lastType = level_->getLastType();
        lastAmount = level_->getLastAmount();
    }

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

void GameScene::render(RenderWindow &window) {

    window.draw(background_);

    level_->draw(window, font_);

    if (level_->hasActiveRequest() && !level_->isFailed() && !level_->isCompleted()) {
        string req =
                "Process " + std::to_string(lastPid) +
                " requests " + std::to_string(lastAmount) +
                " unit(s) of Resource " + std::to_string(static_cast<int>(lastType) + 1);

        Text requestText(req, font_, 18);
        requestText.setFillColor(Color::Black);
        requestText.setPosition(425.f, 500.f);
        window.draw(requestText);
    }


    window.draw(timerText);
    for (auto &btn: btns_) {
        window.draw(btn);
    }



    if (level_->isCompleted()) {
        Text msg("Level completed!", font_, 40);
        msg.setFillColor(Color::Green);
        msg.setPosition(420.f, 400.f);
        window.draw(msg);
    } else if (level_->isFailed()) {
        Text msg("Level failed! Retry.", font_, 40);
        msg.setFillColor(Color::Red);
        msg.setPosition(420.f, 400.f);
        window.draw(msg);
    }

}

bool GameScene::isComplete() const {
    return level_->isCompleted();

}

void GameScene::print() {
    cerr << "[TEST] Button pressed." << endl;
}

bool GameScene::isFailed() const {
    return level_->isFailed();
}
