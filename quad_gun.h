#ifndef QUAD_GUN_H
#define QUAD_GUN_H


#include "gun.h"
#include "projectile.h"

class QuadGun : public Gun {
public:
    QuadGun(float initRange = 1000.f, float initDamage = 10.f, float initCooldown = 0.1f);
    ~QuadGun() override = default;
    std::vector<std::unique_ptr<Projectile>> fire(sf::Vector2f position, sf::Vector2f direction) override;

};






#endif // QUAD_GUN_H
