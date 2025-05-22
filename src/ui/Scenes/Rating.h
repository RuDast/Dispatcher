// Rating.h
#ifndef RATING_H
#define RATING_H

#include <string>
#include <vector>

class Rating {
public:
    static void saveNickname(const std::string& nickname);
    static bool isNicknameExists(const std::string& nickname);
    static void clearRatings(); // Новый метод для очистки
private:
    static std::vector<std::string> readAllNicknames();
};

#endif // RATING_H