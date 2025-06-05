#ifndef PIERCING_GUN_H
#define PIERCING_GUN_H

#include "gun.h"

class PiercingGun : public Gun {
public:
    PiercingGun(float initRange = 1000.f, float initDamage = 10.f, float initCooldown = 0.5f);

    std::vector<std::unique_ptr<Projectile>> fire(sf::Vector2f position, sf::Vector2f direction) override;
};


#endif // PIERCING_GUN_H
