#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>


class Scene {
public:
    virtual ~Scene() = default;

    virtual void handleInput(const sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};



#endif //SCENE_H
