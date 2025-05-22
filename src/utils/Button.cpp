#include "Button.h"

Button::Button(const sf::Vector2f& size,
               const sf::Vector2f& position,
               const sf::String& label,
               const sf::Font& font,
               std::function<void()> callback)
: rect(size)
, text(label, font, /* characterSize */ 20), onClick(std::move(callback))

{
    rect.setPosition(position);
    rect.setFillColor(sf::Color(100,100,200));
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color::White);

    sf::FloatRect tb = text.getLocalBounds();
    text.setOrigin(tb.left + tb.width/2, tb.top + tb.height/2);
    text.setPosition(
        position.x + size.x/2,
        position.y + size.y/2
    );
}

void Button::handleEvent(const sf::Event& ev) {
    if (ev.type == sf::Event::MouseButtonPressed
     && ev.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mpos(ev.mouseButton.x, ev.mouseButton.y);
        if (rect.getGlobalBounds().contains(mpos)) {
            if (onClick) onClick();
        }
    }
}