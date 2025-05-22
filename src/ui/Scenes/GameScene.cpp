#include "GameScene.h"
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

GameScene::GameScene(RenderWindow &window, const LevelConfig &config) : window_(window),
                                                                        level_config_(config) {
    font_.loadFromFile("../src/resources/font/main_font.ttf");
    level_ = make_unique<Level>(level_config_);
    btns_.push_back(Button({250, 120},
                           {605, 282},
                           "Give",
                           font_,
                           [this]() { level_->handlePlayerChoice(true); }));
    btns_.push_back(Button({250, 120},
                           {475, 412},
                           "Cancel",
                           font_,
                           [this]() { level_->handlePlayerChoice(false); }));
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
    level_->draw(window, font_);

    if (level_->hasActiveRequest() && !level_->isFailed() && !level_->isCompleted()) {
        string req =
                "Process " + std::to_string(lastPid) +
                " requests " + std::to_string(lastAmount) +
                " unit(s) of Resource " + std::to_string(static_cast<int>(lastType) + 1);

        // cout << req << endl;
        Text requestText(req, font_, 18);
        requestText.setFillColor(Color::Black);
        requestText.setPosition(50.f, 50.f + (level_->getProcessCount() + 2) * 40.f);
        window.draw(requestText);
    }

    for (auto &btn: btns_) {
        window.draw(btn);
    }

    if (level_->isCompleted()) {
        Text msg("Level completed!", font_, 24);
        msg.setFillColor(Color::Green);
        msg.setPosition(400.f, 20.f);
        window.draw(msg);
    } else if (level_->isFailed()) {
        Text msg("Level failed! Retry.", font_, 24);
        msg.setFillColor(Color::Red);
        msg.setPosition(400.f, 20.f);
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
