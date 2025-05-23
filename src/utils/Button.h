#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Button : public sf::Drawable {
public:

    Button(const sf::Vector2f& size,
           const sf::Vector2f& position,
           const sf::String& label,
           const sf::Font& font,
           std::function<void()> callback);

    void handleEvent(const sf::Event& ev);

    void setFillColor(const sf::Color& c){ rect.setFillColor(c); }
    void setTextColor(const sf::Color& c){ text.setFillColor(c); }
    void setOutlineColor(const sf::Color& c){ rect.setOutlineColor(c); }

private:
    sf::RectangleShape rect;
    sf::Text           text;
    std::function<void()> onClick;
    sf::Font font;

    sf::SoundBuffer buffer_;
    sf::Sound sound;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(rect, states);
        target.draw(text, states);
    }
};






#endif //BUTTON_H
