#ifndef FAQSCENE_H
#define FAQSCENE_H

#include "../Scene.h"
#include "../../utils/Button.h"
#include <vector>
#include <string>

class FAQScene : public Scene {
public:
    FAQScene();
    void setBackBtnCallback(const std::function<void()>& callback);
    void handleInput(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    void initCrawlText();

    sf::Font font;
    std::function<void()> back_btn_callback_;
    std::vector<Button> btns_;

    // Для эффекта "звёздных войн"
    sf::Text crawlText;
    float textPositionY;
    float crawlSpeed = 50.f; // Пикселей в секунду
    std::vector<std::string> crawlLines = {
        "Frequently Asked Questions",
        "",
        "Q: How to play this game?",
        "A: Use arrow keys to move and space to interact.",
        "",
        "Q: How to save progress?",
        "A: Progress saves automatically between levels.",
        "",
        "Q: How to change controls?",
        "A: Go to Settings from the main menu.",
        "",
        "May the Force be with you!"
    };
};

#endif // FAQSCENE_H