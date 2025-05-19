#include "range.h"
#include "bullet.h"


std::unique_ptr<Projectile> Range::fire(sf::Vector2f position, sf::Vector2f dir) {
    return std::make_unique<Bullet>(position, dir, getVelocity(), getRange());
}


void Range::setRange(float new_range) {
    range = new_range;
}

float Range::getRange() const {
    return range;
}



float Range::getVelocity() const {
    return velocity;
}


void Range::setVelocity(float new_velocity) {
    velocity = new_velocity;
}
