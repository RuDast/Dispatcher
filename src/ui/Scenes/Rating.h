#ifndef RATING_H
#define RATING_H

#include <string>
#include <vector>

class Rating {
public:
    static void saveNickname(const std::string& nickname);
    static bool isNicknameExists(const std::string& nickname); // Делаем метод публичным
private:
    static std::vector<std::string> readAllNicknames();
};

#endif