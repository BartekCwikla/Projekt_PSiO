#include "range.h"
#include "bullet.h"


std::unique_ptr<Projectile> Range::fire(sf::Vector2f position, sf::Vector2f dir) {
    return std::make_unique<Bullet>(position, dir, getVelocity());
}


void Range::setRange(float new_range) {
    range = new_range;
}

float Range::getVelocity() const {
    return velocity;
}
