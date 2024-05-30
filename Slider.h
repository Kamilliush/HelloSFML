#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics.hpp>

class Slider {
public:
    Slider(const sf::Vector2f& position, const sf::Vector2f& size);

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    float getValue() const;
    void setValue(float value); // Dodaj funkcjê ustawiaj¹c¹ wartoœæ suwaka

private:
    sf::RectangleShape track;
    sf::RectangleShape thumb;
    bool dragging;
    float value; // 0.0 to 1.0

    bool isMouseOverThumb(const sf::Vector2i& mousePos) const;
};

#endif // SLIDER_H
