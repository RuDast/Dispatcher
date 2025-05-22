#ifndef FAQSCENE_H
#define FAQSCENE_H

#include "../Scene.h"
#include "../../utils/Button.h"
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class FAQScene : public Scene {
public:
    FAQScene();
    void setBackBtnCallback(const std::function<void()>& callback);
    void handleInput(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void play_sound();
private:
    void initCrawlText();
    bool loadTextFromFile(const std::string& path); // Новая функция загрузки



    sf::Font font;
    std::function<void()> back_btn_callback_;
    std::vector<Button> btns_;

    // Для эффекта прокрутки
    sf::Text crawlText;
    float textPositionY;
    float crawlSpeed = 50.f;
    std::vector<std::string> crawlLines; // Теперь загружается из файла

    // Музыка
    sf::SoundBuffer buffer_faq;
    sf::Sound faq_sound;
    bool musicPlaying = false; // Флаг воспроизведения
};

#endif // FAQSCENE_H