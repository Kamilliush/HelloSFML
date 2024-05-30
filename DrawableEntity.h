#ifndef DRAWABLE_ENTITY_H
#define DRAWABLE_ENTITY_H

#include <SFML/Graphics.hpp>

class DrawableEntity {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
};

#endif // DRAWABLE_ENTITY_H
