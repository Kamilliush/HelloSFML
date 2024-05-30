#include "Button.h"

Button::Button(const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size) {
    button.setSize(size);
    button.setPosition(position);
    button.setFillColor(sf::Color(143, 122, 102)); // Kolor przycisków na rgb(143, 122, 102)

    if (!font.loadFromFile("arial.ttf")) {
        // Error handling
    }

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color(249, 246, 242)); // Kolor czcionki na rgb(249, 246, 242)
    buttonText.setPosition(
        position.x + (size.x - buttonText.getLocalBounds().width) / 2,
        position.y + (size.y - buttonText.getLocalBounds().height) / 2 - 5
    );
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(buttonText);
}

bool Button::isClicked(const sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
