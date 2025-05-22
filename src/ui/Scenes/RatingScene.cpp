// RatingScene.cpp
#include "RatingScene.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "Rating.h"

RatingScene::RatingScene() {
    if (!font.loadFromFile("../src/resources/font/main_font.ttf")) {
        std::cerr << "Error loading font in RatingScene" << std::endl;
    }

    // Кнопка назад
    btns_.push_back(Button({250, 120}, {50, 50}, "Back", font, [this]() {
        if (back_btn_callback_) back_btn_callback_();
    }));

    // Заголовок
    titleText.setFont(font);
    titleText.setString("Player Ratings");
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(100, 50);

    // Загрузка рейтингов
    loadRatings();
}

void RatingScene::loadRatings() {
    auto players = Rating::getAllPlayers();

    // Очищаем предыдущие тексты
    ratingTexts.clear();

    // Заголовки таблицы
    sf::Text headerRank, headerPlayer, headerScore;
    headerRank.setFont(font);
    headerPlayer.setFont(font);
    headerScore.setFont(font);

    // Общие параметры заголовков
    for (auto* text : {&headerRank, &headerPlayer, &headerScore}) {
        text->setCharacterSize(30);
        text->setFillColor(sf::Color::Red);
    }

    // Установка текста и позиций заголовков
    headerRank.setString("Rank");
    headerRank.setPosition(500, 100);

    headerPlayer.setString("Player");
    headerPlayer.setPosition(600, 100);

    headerScore.setString("Score");
    headerScore.setPosition(800, 100);

    ratingTexts.push_back(headerRank);
    ratingTexts.push_back(headerPlayer);
    ratingTexts.push_back(headerScore);

    // Данные игроков
    for (size_t i = 0; i < players.size(); ++i) {
        // Ранг
        sf::Text rankText;
        rankText.setFont(font);
        rankText.setString(std::to_string(i + 1));
        rankText.setCharacterSize(24);
        rankText.setFillColor(sf::Color::Black);
        rankText.setPosition(500, 140 + i * 40);

        // Никнейм
        sf::Text playerText;
        playerText.setFont(font);
        playerText.setString(players[i].first);
        playerText.setCharacterSize(24);
        playerText.setFillColor(sf::Color::Black);
        playerText.setPosition(600, 140 + i * 40);

        // Очки
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString(std::to_string(players[i].second));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(800, 140 + i * 40);

        ratingTexts.push_back(rankText);
        ratingTexts.push_back(playerText);
        ratingTexts.push_back(scoreText);
    }

    // Если нет игроков
    if (players.empty()) {
        sf::Text emptyText;
        emptyText.setFont(font);
        emptyText.setString("No players yet");
        emptyText.setCharacterSize(24);
        emptyText.setFillColor(sf::Color::White);
        emptyText.setPosition(500, 140);
        ratingTexts.push_back(emptyText);
    }
}

void RatingScene::setBackBtnCallback(const std::function<void()> &callback) {
    back_btn_callback_ = callback;
}

void RatingScene::handleInput(const sf::Event &event) {
    for (auto &btn: btns_) {
        btn.handleEvent(event);
    }
}

void RatingScene::update(float deltaTime) {
    // Можно добавить обновление рейтинга по таймеру, если нужно
}

void RatingScene::render(sf::RenderWindow &window) {
    window.draw(titleText);

    for (auto &btn: btns_) {
        window.draw(btn);
    }

    for (auto &text: ratingTexts) {
        window.draw(text);
    }
}