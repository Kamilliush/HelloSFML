#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "DrawableEntity.h"

class Button : public DrawableEntity {
public:
    Button(const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size);

    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override {}
    bool isClicked(const sf::Vector2i& mousePos);

private:
    sf::RectangleShape button;
    sf::Text buttonText;
    sf::Font font;
};

#endif // BUTTON_H
