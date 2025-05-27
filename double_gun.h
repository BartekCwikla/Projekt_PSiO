#ifndef DOUBLE_GUN_H
#define DOUBLE_GUN_H


#include "gun.h"
#include "projectile.h"

class DoubleGun : public Gun {
public:
    std::vector<std::unique_ptr<Projectile>> fire(sf::Vector2f position, sf::Vector2f direction);

};




#endif // DOUBLE_GUN_H
