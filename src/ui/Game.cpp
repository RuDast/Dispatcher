#include "Game.h"
#include <iostream>

#include "../core/structures.h"
#include "../utils/Config.h"

using namespace sf;
using namespace std;

Game::Game() : window_(VideoMode(game::win_width, game::win_height),
                       game::win_title),
               main_menu_scene_(),
               rating_scene_(),
               settings_scene_(), faq_scene_() {
    main_menu_scene_.setRatingBtnCallback([this]() {
        this->switchToRatingScene();
    });
    main_menu_scene_.setSettingsBtnCallback([this]() {
    this->switchToSettingsScene();
    });
    main_menu_scene_.setFAQBtnCallback([this]() {
    this->switchToFAQScene();
    });
    main_menu_scene_.setLevSelCallback([this](const unsigned level) {
        this->startLevel(level);
    });


    rating_scene_.setBackBtnCallback([this]() {
        this->switchToMainScene();
    });
    settings_scene_.setBackBtnCallback([this]() {
        this->switchToMainScene();
    });
    faq_scene_.setBackBtnCallback([this]() {
    this->switchToMainScene();
    });

    current_scene_ = &main_menu_scene_;

    run();
}

void Game::run() {
    Clock clock;
    while (window_.isOpen()) {
        const float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    if (Event event; window_.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window_.close();
            return;
        }

        if (current_scene_) {
            current_scene_->handleInput(window_, event);
        }
    }
}

void Game::update(const float dt) const {
    if (current_scene_) {
        current_scene_->update(dt);
    }
}

void Game::render() {
    window_.clear();
    if (current_scene_) {
        current_scene_->render(window_);
    }
    window_.display();
}

void Game::switchToRatingScene() {
    current_scene_ = &rating_scene_;
}

void Game::switchToSettingsScene()
{
    current_scene_ = &settings_scene_;
}

void Game::switchToFAQScene()
{
    current_scene_ = &faq_scene_;
}

void Game::switchToMainScene() {
    current_scene_ = &main_menu_scene_;
}

void Game::startLevel(unsigned level) {
    delete game_scene_;
    LevelConfig cfg;

    cfg.resources_ = {
        { ResourceType::Type1, 6 },
        { ResourceType::Type2, 3 }
    };

    cfg.processes_ = {
        { 1, { 5, 2 } },
        { 2, { 2, 3 } },
        { 3, { 6, 3 } },
        { 4, { 1, 1 } }
    };

    game_scene_ = new GameScene(window_, cfg);
    current_scene_ = game_scene_;
    game_scene_->setBackBtnCallback([this]() {
    this->switchToMainScene();
    });
}
