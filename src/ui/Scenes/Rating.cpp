// Rating.cpp
#include "Rating.h"
#include <fstream>
#include <algorithm>
#include <sstream>

const std::string Rating::RATING_FILE_PATH = "../src/resources/rating.txt";

void Rating::savePlayer(const std::string& nickname, int score) {
    auto players = readAllPlayers();

    // Проверяем, существует ли уже игрок
    auto it = std::find_if(players.begin(), players.end(),
        [&nickname](const auto& p) { return p.first == nickname; });

    if (it == players.end()) {
        players.emplace_back(nickname, score);
        writeAllPlayers(players);
    }
}

std::vector<std::pair<std::string, int>> Rating::getAllPlayers() {
    auto players = readAllPlayers();
    // Сортируем по убыванию очков
    std::sort(players.begin(), players.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    return players;
}

void Rating::updatePlayerScore(const std::string& nickname, int newScore) {
    auto players = readAllPlayers();
    for (auto& player : players) {
        if (player.first == nickname) {
            player.second = newScore;
            break;
        }
    }
    writeAllPlayers(players);
}

std::vector<std::pair<std::string, int>> Rating::readAllPlayers() {
    std::vector<std::pair<std::string, int>> players;
    std::ifstream file(RATING_FILE_PATH);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string nickname;
            int score;
            if (iss >> nickname >> score) {
                players.emplace_back(nickname, score);
            }
        }
        file.close();
    }
    return players;
}

void Rating::writeAllPlayers(const std::vector<std::pair<std::string, int>>& players) {
    std::ofstream file(RATING_FILE_PATH);
    if (file.is_open()) {
        for (const auto& player : players) {
            file << player.first << " " << player.second << "\n";
        }
        file.close();
    }
}

void Rating::clearRatings() {
    std::ofstream file(RATING_FILE_PATH, std::ios::trunc);
    file.close();
}