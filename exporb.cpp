#include "exporb.h"

ExpOrb::ExpOrb(const sf::Vector2f& pos, float value)
    :
    greenOrb("./assets/ExpOrb", "exporb", 4, 0.07,1),
    expValue(value)

{
    body.setRadius(8.f);
    body.setFillColor(sf::Color::Yellow);
    body.setOrigin(8.f, 8.f); // środek
    body.setPosition(pos);

    greenOrb.setPosition(pos.x, pos.y);
}

void ExpOrb::render(sf::RenderWindow& window, float dt) {
    greenOrb.setPosition(body.getPosition().x, body.getPosition().y);
    greenOrb.update(dt);
    greenOrb.draw(window);
}

sf::FloatRect ExpOrb::getBounds() const {
    return body.getGlobalBounds();
}

float ExpOrb::getExpValue() const {
    return expValue;
}
