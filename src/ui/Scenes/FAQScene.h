#ifndef FAQSCENE_H
#define FAQSCENE_H
#include "../Scene.h"
#include "../../utils/Button.h"

class FAQScene : public Scene{
public:
    FAQScene();

    void setBackBtnCallback(const std::function<void()>& callback);

    void handleInput(sf::RenderWindow &window, const sf::Event &event) override;

    void update(float deltaTime) override;

    void render(sf::RenderWindow &window) override;

private:
    sf::Font font;
    std::function<void()> back_btn_callback_;
    std::vector<Button> btns_;

};



#endif //FAQSCENE_H
