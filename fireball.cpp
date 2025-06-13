#include "fireball.h"
#include "fireball_projectile.h"
#include <iostream>

float Fireball::getDamage() const
{
    return damage;
}

void Fireball::setDamage(float newDamage)
{
    damage = newDamage;
}

float Fireball::getRange() const
{
    return range;
}

void Fireball::setRange(float newRange)
{
    range = newRange;
}

float Fireball::getSpeed() const
{
    return speed;
}

void Fireball::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

Fireball::Fireball(float range, float damage) : SuperPower("./assets/SuperPowers/fireball.png", 20.f, "Fireball"), damage(damage), range(range), speed(400.f) {

}

ActionResult Fireball::activate(const sf::Vector2f& position, const sf::Vector2f& direction) {
    ActionResult result;
    if (!isReady()) {
        return result;
    }
    cooldownClock.restart();
    result.fireball_projectile = std::make_unique<FireballProjectile>(
            position, direction, damage, range, speed
            );
    return result;
}
