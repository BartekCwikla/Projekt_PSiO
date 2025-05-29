#ifndef EXPLODING_GUN_H
#define EXPLODING_GUN_H

#include "gun.h"

class ExplodingGun : public Gun {
public:
    ExplodingGun(float initRange = 1000.f, float initDamage = 10.f, float initCooldown = 0.1f);
    ~ExplodingGun() override = default;
    std::vector<std::unique_ptr<Projectile>> fire(sf::Vector2f position, sf::Vector2f direction) override;
};

#endif // EXPLODING_GUN_H
