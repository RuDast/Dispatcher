// Rating.cpp
#include "Rating.h"
#include <fstream>
#include <algorithm>
#include <iostream>

std::vector<std::string> Rating::readAllNicknames() {
    std::vector<std::string> nicknames;
    std::ifstream file("../src/resources/raiting.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                nicknames.push_back(line);
            }
        }
        file.close();
    }
    return nicknames;
}

bool Rating::isNicknameExists(const std::string& nickname) {
    auto nicknames = readAllNicknames();
    return std::find(nicknames.begin(), nicknames.end(), nickname) != nicknames.end();
}

void Rating::saveNickname(const std::string& nickname) {
    if (nickname.empty() || isNicknameExists(nickname)) {
        return; // Не сохраняем пустые никнеймы или уже существующие
    }

    std::ofstream file("../src/resources/raiting.txt", std::ios::app);
    if (file.is_open()) {
        file << nickname << std::endl;
        file.close();
    } else {
        std::cerr << "Unable to open raiting.txt file" << std::endl;
    }
}