#include "Slider.h"

Slider::Slider(const sf::Vector2f& position, const sf::Vector2f& size)
    : dragging(false), value(0.5f) { // Ustaw pocz¹tkow¹ wartoœæ na 0.5
    track.setSize(size);
    track.setPosition(position);
    track.setFillColor(sf::Color(200, 200, 200));

    thumb.setSize(sf::Vector2f(size.y, size.y));
    thumb.setOrigin(thumb.getSize() / 2.0f);
    thumb.setPosition(position.x + value * size.x, position.y + size.y / 2.0f);
    thumb.setFillColor(sf::Color(100, 100, 100));
}

void Slider::draw(sf::RenderWindow& window) {
    window.draw(track);
    window.draw(thumb);
}

void Slider::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && isMouseOverThumb(mousePos)) {
            dragging = true;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            dragging = false;
        }
    }

    if (event.type == sf::Event::MouseMoved && dragging) {
        float newX = static_cast<float>(mousePos.x);
        newX = std::max(track.getPosition().x, std::min(newX, track.getPosition().x + track.getSize().x));
        thumb.setPosition(newX, thumb.getPosition().y);

        value = (newX - track.getPosition().x) / track.getSize().x;
    }
}

float Slider::getValue() const {
    return value;
}

void Slider::setValue(float newValue) {
    value = newValue;
    thumb.setPosition(track.getPosition().x + value * track.getSize().x, thumb.getPosition().y);
}

bool Slider::isMouseOverThumb(const sf::Vector2i& mousePos) const {
    return thumb.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
