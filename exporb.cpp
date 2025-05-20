#include "exporb.h"

ExpOrb::ExpOrb(const sf::Vector2f& pos, float value) : expValue(value) {
    body.setRadius(8.f);
    body.setFillColor(sf::Color::Yellow);
    body.setOrigin(8.f, 8.f); // środek
    body.setPosition(pos);
}

void ExpOrb::render(sf::RenderWindow& window) {
    window.draw(body);
}

sf::FloatRect ExpOrb::getBounds() const {
    return body.getGlobalBounds();
}

float ExpOrb::getExpValue() const {
    return expValue;
}
