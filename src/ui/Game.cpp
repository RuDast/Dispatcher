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
               settings_scene_(),
               faq_scene_(),
               background({game::win_width, game::win_height}) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
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

    background.setFillColor(Color::White);

    rating_scene_.setBackBtnCallback([this]() {
        this->switchToMainScene();
    });
    settings_scene_.setBackBtnCallback([this]() {
        this->switchToMainScene();
    });
    faq_scene_.setBackBtnCallback([this]() {
        this->switchToMainScene();
    });
    main_menu_scene_.setLevSelCallback([this](const unsigned level) {
        this->startLevel(level);
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
    Event event{};
    while (window_.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window_.close();
            return;
        }

        if (current_scene_) {
            current_scene_->handleInput(event);
        }
    }
}

void Game::update(const float dt) {
    if (pendingEnd_) {
        endTimer_ -= dt;
        if (endTimer_ <= 0.f) {
            // После 2 секунд — закрываем уровень и сбрасываем флаг
            endLevel();
            pendingEnd_ = false;
            game_status_ = GameStatus::None;
        }
        // во время ожидания не генерим новые запросы
        return;
    }


    if (current_scene_) {
        current_scene_->update(dt);
    }

    if (current_scene_ == game_scene_) {
        if (current_scene_ == game_scene_) {
            if (game_scene_->isFailed()) {
                // провал — сразу планируем выход
                pendingEnd_ = true;
                endTimer_ = 2.0f;
                game_status_ = GameStatus::Fail;
            } else if (game_scene_->isComplete()) {
                // успех — планируем выход
                pendingEnd_ = true;
                endTimer_ = 2.0f;
                game_status_ = GameStatus::Success;
            }
        }
    }
}

void Game::render() {
    window_.clear();
    window_.draw(background);
    if (current_scene_) {
        current_scene_->render(window_);
    }
    window_.display();
}

void Game::switchToRatingScene() {
    current_scene_ = &rating_scene_;
}

void Game::switchToSettingsScene() {
    current_scene_ = &settings_scene_;
}

void Game::switchToFAQScene() {
    current_scene_ = &faq_scene_;
}

void Game::switchToMainScene() {
    current_scene_ = &main_menu_scene_;
}

void Game::startLevel(unsigned level) {
    delete game_scene_;
    LevelConfig cfg;

    cfg.resources_ = {
        {ResourceType::Type1, 6},
        {ResourceType::Type2, 3}
    };

    cfg.processes_ = {
        {1, {5, 2}},
        {2, {2, 3}},
        {3, {6, 3}},
        {4, {1, 1}}
    };

    game_scene_ = new GameScene(window_, cfg);
    current_scene_ = game_scene_;
    game_scene_->setBackBtnCallback([this]() {
    this->switchToMainScene();
    });
}

void Game::endLevel() {
    delete game_scene_;
    game_scene_ = nullptr;
    main_menu_scene_.reset();
    current_scene_ = &main_menu_scene_;
}
