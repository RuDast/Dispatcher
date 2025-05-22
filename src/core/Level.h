#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "structures.h"


class Level {
    LevelConfig config_;

    const float CELL_WIDTH  = 100.f;
    const float CELL_HEIGHT = 40.f;

    const float ORIGIN_X = 50.f;
    const float ORIGIN_Y = 50.f;

    const sf::Color GRID_COLOR {200, 200, 200};
    const sf::Color TEXT_COLOR {50,  50,  50};

public:
    Level(const LevelConfig& level_config);

    void draw(sf::RenderWindow& win, const sf::Font& font);

};



#endif //LEVEL_H
