#include "Game.h"

#include <iostream>

#include "../utils/Config.h"

using namespace sf;
using namespace std;

Game::Game() : window_(VideoMode(game::win_width, game::win_height),
                       game::win_title),
               main_menu_scene_(),
               rating_scene_(),
               settings_scene_() {
    main_menu_scene_.setRatBtnCallback([this]() {
        this->switchToRatingScene();
    });
    rating_scene_.setBackBtnCallback([this]() {
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

void Game::switchToMainScene() {
    current_scene_ = &main_menu_scene_;
}
