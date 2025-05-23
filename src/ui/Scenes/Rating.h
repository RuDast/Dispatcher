// Rating.h
#ifndef RATING_H
#define RATING_H

#include <string>
#include <vector>
#include <utility> // для std::pair

class Rating {
public:
    static void savePlayer(const std::string& nickname, int score = 0);
    static std::vector<std::pair<std::string, int>> getAllPlayers();
    static void updatePlayerScore(const std::string& nickname, int newScore);
    static void clearRatings();


private:
    static const std::string RATING_FILE_PATH;
    static std::vector<std::pair<std::string, int>> readAllPlayers();
    static void writeAllPlayers(const std::vector<std::pair<std::string, int>>& players);
};

#endif // RATING_H