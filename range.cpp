#include "range.h"
#include "bullet.h"


std::vector<std::unique_ptr<Projectile>> Range::fire(sf::Vector2f position, sf::Vector2f dir) {
    std::vector<std::unique_ptr<Projectile>> projectiles;
    projectiles.push_back(std::make_unique<Bullet>(position, dir, getVelocity(), getRange(), getDamage()));
    return projectiles;
}

float Range::getExplosionRange() const
{
    return explosionRange;
}

void Range::setExplosionRange(float newExplosionRange)
{
    explosionRange = newExplosionRange;
}

bool Range::getIsPiercing() const
{
    return isPiercing;
}

void Range::setIsPiercing(bool newIsPiercing)
{
    isPiercing = newIsPiercing;
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
