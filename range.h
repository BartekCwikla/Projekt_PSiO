#include "weapon.h"

#ifndef RANGE_H
#define RANGE_H


class Range : public Weapon {
private:
    float range = 1000;
    float velocity = 100;
    float explosionRange = 0;
    bool isPiercing = false;

public:
    void setRange(float range);
    float getRange() const;

    float getVelocity() const;
    void setVelocity(float);

    virtual std::vector<std::unique_ptr<Projectile>> fire(sf::Vector2f, sf::Vector2f);
    float getExplosionRange() const;
    void setExplosionRange(float newExplosionRange);
    bool getIsPiercing() const;
    void setIsPiercing(bool newIsPiercing);
};



#endif // RANGE_H
