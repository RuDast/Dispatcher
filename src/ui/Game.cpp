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

    buffer.loadFromFile("../src/resources/sounds/wasted.wav");
    sound_wasted.setBuffer(buffer);



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
            if (current_scene_ != &settings_scene_)
            current_scene_->handleInput(event);
            else
                dynamic_cast<SettingsScene*>(current_scene_)->handleInput(window_, event);
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
                sound_wasted.play();
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
    faq_scene_.play_sound();
}

void Game::switchToMainScene() {
    current_scene_ = &main_menu_scene_;
}

void Game::startLevel(unsigned level) {
    delete game_scene_;
    LevelConfig cfg1;

    cfg1.resources_ = {
        {ResourceType::Type1, 6},
        {ResourceType::Type2, 3}
    };

    cfg1.processes_ = {
        {1, {5, 2}},
        {2, {2, 3}},
        {3, {6, 3}},
        {4, {1, 1}}
    };

    LevelConfig cfg2;
    cfg2.resources_ = {
        { ResourceType::Type1, 5 },
        { ResourceType::Type2, 7 },
        { ResourceType::Type3, 4 }
    };
    cfg2.processes_ = {
        { 1, { 1, 2, 1 } },  // процесс 1: нужно 1×R1, 2×R2, 1×R3
        { 2, { 2, 1, 1 } },  // процесс 2
        { 3, { 3, 2, 2 } },  // процесс 3
        { 4, { 4, 1, 3 } },  // процесс 4
        { 5, { 2, 3, 1 } },  // процесс 5
        { 6, { 1, 1, 2 } }   // процесс 6
    };

    // --- Конфиг третьего уровня: 5 типов ресурсов, 9 процессов ---
    LevelConfig cfg3;
    cfg3.resources_ = {
        { ResourceType::Type1, 10 },
        { ResourceType::Type2, 8  },
        { ResourceType::Type3, 6  },
        { ResourceType::Type4, 7  },
        { ResourceType::Type5, 5  }
    };
    cfg3.processes_ = {
        { 1, { 2, 1, 1, 0, 2 } },
        { 2, { 1, 2, 0, 1, 1 } },
        { 3, { 3, 1, 2, 1, 0 } },
        { 4, { 0, 1, 1, 2, 2 } },
        { 5, { 1, 0, 2, 1, 1 } },
        { 6, { 2, 2, 1, 0, 1 } },
        { 7, { 1, 1, 1, 1, 1 } },
        { 8, { 0, 2, 2, 1, 0 } },
        { 9, { 1, 0, 1, 2, 2 } }
    };

    if (level == 1)
        game_scene_ = new GameScene(window_, cfg1);
    else if (level == 2)
        game_scene_ = new GameScene(window_, cfg2);
    else if (level == 3)
        game_scene_ = new GameScene(window_, cfg3);
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
