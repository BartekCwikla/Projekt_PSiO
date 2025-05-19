#include "weapon.h"

#ifndef RANGE_H
#define RANGE_H


class Range : public Weapon {
private:
    float range;
    float velocity = 100;

public:
    void setRange(float range);
    float getRange() const;

    float getVelocity() const;
    void setVelocity(float);

    virtual std::unique_ptr<Projectile> fire(sf::Vector2f, sf::Vector2f);
};



#endif // RANGE_H
