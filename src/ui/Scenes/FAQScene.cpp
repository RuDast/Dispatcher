#include "FAQScene.h"
#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;

FAQScene::FAQScene() {
    if (!font.loadFromFile("../src/resources/font/main_font.ttf")) {
        cerr << "Error loading FAQ font" << endl;
    }

    // Кнопка назад (правый верхний угол с отступом 20px)
    btns_.push_back(Button({250, 50}, {1200 - 250 - 20, 20}, "Back", font, [this]() {
        if (back_btn_callback_) {
            back_btn_callback_();
            faq_sound.stop();
        }
    }));

    // Загружаем текст из файла
    if (!loadTextFromFile("../src/resources/FAQ.txt")) {
        // Если файл не загружен, используем текст по умолчанию
        crawlLines = {
            "Frequently Asked Questions",
            "",
            "Error: Could not load FAQ.txt",
            "Please make sure the file exists",
            "",
            "Default questions will be shown",
            "",
            "Q: How to play?",
            "A: Use keyboard controls",
            "",
            "Q: How to save?",
            "A: Progress saves automatically"
        };
    }
    buffer_faq.loadFromFile("../src/resources/sounds/snd.wav");
    faq_sound.setBuffer(buffer_faq);

    initCrawlText();

}
bool FAQScene::loadTextFromFile(const std::string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Failed to open FAQ file: " << path << endl;
        return false;
    }

    crawlLines.clear();
    string line;
    while (getline(file, line)) {
        crawlLines.push_back(line);
    }
    file.close();
    return true;
}

void FAQScene::initCrawlText() {
    crawlText.setFont(font);
    crawlText.setCharacterSize(28);  // Увеличим размер для лучшей читаемости
    crawlText.setFillColor(sf::Color(255, 215, 0));  // Золотой цвет
    crawlText.setOutlineColor(sf::Color::Black);
    crawlText.setOutlineThickness(1.f);

    // Собираем весь текст в одну строку с переносами
    string fullText;
    for (const auto& line : crawlLines) {
        fullText += line + "\n";
    }
    crawlText.setString(fullText);

    // Центрируем по горизонтали
    FloatRect textBounds = crawlText.getLocalBounds();
    crawlText.setOrigin(textBounds.width/2, 0);
    crawlText.setPosition(1200/2, 705);  // Центр по X, начинаем снизу экрана
    textPositionY = 705;  // Стартовая позиция (низ экрана)
}

void FAQScene::setBackBtnCallback(const std::function<void()>& callback) {
    back_btn_callback_ = callback;
}

void FAQScene::handleInput(const Event& event) {
    for (auto& btn : btns_) {
        btn.handleEvent(event);
    }

    // Ускорение/замедление прокрутки по клавишам
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Up) {
            crawlSpeed += 20.f;
        } else if (event.key.code == Keyboard::Down) {
            crawlSpeed = max(10.f, crawlSpeed - 20.f);
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::M) { // M - mute/unmute
            if (musicPlaying) {
                faq_sound.pause();
                musicPlaying = false;
            } else {
                faq_sound.play();
                musicPlaying = true;
            }
        }
    }
}

void FAQScene::update(float deltaTime) {
    // Двигаем текст вверх
    textPositionY -= crawlSpeed * deltaTime;
    crawlText.setPosition(600, textPositionY);

    // Если текст полностью ушел вверх, начинаем заново
    if (textPositionY < -crawlText.getLocalBounds().height) {
        textPositionY = 705;
    }

}

void FAQScene::render(RenderWindow& window) {
    // Очищаем экран (тёмно-синий для космического фона)
    window.clear(sf::Color(10, 10, 30));

    // Рисуем звёзды (если есть)
    static vector<sf::CircleShape> stars;
    if (stars.empty()) {
        for (int i = 0; i < 150; ++i) {
            sf::CircleShape star(rand() % 2 + 1);
            star.setPosition(rand() % 1200, rand() % 705);  // На весь экран
            star.setFillColor(sf::Color(200 + rand() % 55, 200 + rand() % 55, 200 + rand() % 55));
            stars.push_back(star);
        }
    }
    for (auto& star : stars) {
        window.draw(star);
    }

    // Рисуем текст
    window.draw(crawlText);

    // Рисуем кнопки поверх всего
    for (auto& btn : btns_) {
        window.draw(btn);
    }
}

void FAQScene::play_sound() {
    faq_sound.play();
}



