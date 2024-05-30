#include "Tile.h"
#include <cmath>

Tile::Tile(int value, const sf::Vector2f& position, float tileSize, sf::Font& font)
    : value(value), targetPosition(position), currentPosition(position), moving(false), tileSize(tileSize), font(font) {}

Tile::Tile(const Tile& other)
    : value(other.value), targetPosition(other.targetPosition), currentPosition(other.currentPosition),
    moving(other.moving), tileSize(other.tileSize), font(other.font) {}

Tile& Tile::operator=(const Tile& other) {
    if (this != &other) {
        value = other.value;
        targetPosition = other.targetPosition;
        currentPosition = other.currentPosition;
        moving = other.moving;
        tileSize = other.tileSize;
        font = other.font;
    }
    return *this;
}

int Tile::getValue() const { return value; }
void Tile::setValue(int val) { value = val; }

sf::Vector2f Tile::getPosition() const { return currentPosition; }
void Tile::setTargetPosition(const sf::Vector2f& position) { targetPosition = position; moving = true; }

bool Tile::isMoving() const { return moving; }

void Tile::update(float deltaTime) {
    if (moving) {
        sf::Vector2f direction = targetPosition - currentPosition;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance < 1.0f) {
            currentPosition = targetPosition;
            moving = false;
        }
        else {
            direction /= distance;
            currentPosition += direction * 500.0f * deltaTime;
        }
    }
}

void Tile::draw(sf::RenderWindow& window) {
    sf::RectangleShape tileShape(sf::Vector2f(tileSize, tileSize));
    tileShape.setPosition(currentPosition);
    tileShape.setFillColor(getColor());
    tileShape.setOutlineThickness(5);
    tileShape.setOutlineColor(sf::Color(187, 173, 160)); // Kolor ramek dooko³a pól na rgb(187, 173, 160)
    window.draw(tileShape);

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(value));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(currentPosition.x + tileSize / 2 - text.getLocalBounds().width / 2, currentPosition.y + tileSize / 2 - text.getLocalBounds().height / 2);
    window.draw(text);
}

sf::Color Tile::getColor() const {
    if (value == 0) return sf::Color(205, 193, 180); // Kolor pustego pola na rgb(205, 193, 180)
    static std::map<int, sf::Color> colorMap = {
        {2, sf::Color(238, 228, 218)},
        {4, sf::Color(237, 224, 200)},
        {8, sf::Color(242, 177, 121)},
        {16, sf::Color(245, 149, 99)},
        {32, sf::Color(246, 124, 95)},
        {64, sf::Color(246, 94, 59)},
        {128, sf::Color(237, 207, 114)},
        {256, sf::Color(237, 204, 97)},
        {512, sf::Color(237, 200, 80)},
        {1024, sf::Color(237, 197, 63)},
        {2048, sf::Color(237, 194, 46)},
    };

    auto it = colorMap.find(value);
    if (it != colorMap.end()) {
        return it->second;
    }
    else {
        return sf::Color(60, 58, 50);
    }
}
