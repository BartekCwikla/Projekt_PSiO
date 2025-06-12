#ifndef FIREBALL_H
#define FIREBALL_H

#include "superpower.h"

class Fireball : public SuperPower {
private:
    float damage;
    float range;
    float speed;
public:
    Fireball(float range, float damage);
    ActionResult activate(const sf::Vector2f& position, const sf::Vector2f& direction);
    float getDamage() const;
    void setDamage(float newDamage);
    float getRange() const;
    void setRange(float newRange);
    float getSpeed() const;
    void setSpeed(float newSpeed);
};


#endif // FIREBALL_H
