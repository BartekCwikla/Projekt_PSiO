#include "range.h"

#ifndef GUN_H
#define GUN_H


class Gun : public Range {
public:
    Gun(float initRange = 1000.f, float initDamage = 10.f, float initCooldown = 0.5f);
    ~Gun() override = default;

    std::vector<std::unique_ptr<Projectile>> fire(sf::Vector2f position, sf::Vector2f direction) override;

    void upgrade() override;

protected:
    float cooldownTime;
    sf::Clock coolDown;
};


#endif // GUN_H
