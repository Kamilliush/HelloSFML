#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <map>
#include "DrawableEntity.h"

class Tile : public DrawableEntity {
public:
    Tile(int value, const sf::Vector2f& position, float tileSize, sf::Font& font);
    Tile(const Tile& other);
    Tile& operator=(const Tile& other);

    int getValue() const;
    void setValue(int val);
    sf::Vector2f getPosition() const;
    void setTargetPosition(const sf::Vector2f& position);
    bool isMoving() const;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    int value;
    sf::Vector2f targetPosition;
    sf::Vector2f currentPosition;
    bool moving;
    float tileSize;
    sf::Font& font;

    sf::Color getColor() const;
};

#endif // TILE_H
