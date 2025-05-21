#ifndef RATINGSCENE_H
#define RATINGSCENE_H
#include "../Scene.h"


class RatingScene : public Scene {
public:
    RatingScene();

    void handleInput(sf::RenderWindow &window, const sf::Event &event) override;

    void update(float deltaTime) override;

    void render(sf::RenderWindow &window) override;

private:
    sf::RectangleShape test_;
};


#endif //RATINGSCENE_H
