// RatingScene.h
#ifndef RATINGSCENE_H
#define RATINGSCENE_H

#include "../Scene.h"
#include "../../utils/Button.h"
#include <vector>
#include <string>

class RatingScene : public Scene {
public:
    RatingScene();
    void setBackBtnCallback(const std::function<void()>& callback);
    void handleInput(const sf::Event &event);
    void update(float deltaTime) override;
    void render(sf::RenderWindow &window) override;
    void refreshRatings();
    void loadRatings();
private:


    sf::Font font;
    std::function<void()> back_btn_callback_;
    std::vector<Button> btns_;
    std::vector<sf::Text> ratingTexts;
    std::vector<std::string> nicknames;
    sf::Text titleText;
};

#endif // RATINGSCENE_H