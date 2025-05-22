#ifndef RATINGSCENE_H
#define RATINGSCENE_H
#include "../Scene.h"
#include "../../utils/Button.h"

class RatingScene : public Scene {
public:
    RatingScene();

    void setBackBtnCallback(const std::function<void()>& callback);

    void handleInput(const sf::Event &event) override;

    void update(float deltaTime) override;

    void render(sf::RenderWindow &window) override;

private:
    sf::Font font;
    std::function<void()> back_btn_callback_;
    std::vector<Button> btns_;
    sf::Text authNotificationText;
    bool showAuthNotification = false;

};

#endif //RATINGSCENE_H
