#ifndef DOUBLE_GUN_H
#define DOUBLE_GUN_H


#include "gun.h"
#include "projectile.h"

class DoubleGun : public Gun {
public:
   DoubleGun(float initRange = 1000.f, float initDamage = 10.f, float initCooldown = 0.1f);
   ~DoubleGun() override = default;
    std::vector<std::unique_ptr<Projectile>> fire(sf::Vector2f position, sf::Vector2f direction) override;

};




#endif // DOUBLE_GUN_H
