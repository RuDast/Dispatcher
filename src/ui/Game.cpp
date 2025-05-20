#include "Game.h"

#include <iostream>

#include "../utils/Config.h"

using namespace sf;
using namespace std;

Game::Game() : window_(VideoMode(game::win_width, game::win_height),
                       game::win_title),
               mainMenuScene()
{
    current_scene_ = &mainMenuScene;
}

void Game::run() {
    while (window_.isOpen()) {
        processEvents();
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

void Game::render() {
    window_.clear();
    if (current_scene_) {
        current_scene_->render(window_);
    }
    window_.display();
}
