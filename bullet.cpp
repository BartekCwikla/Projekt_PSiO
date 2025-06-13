#include "bullet.h"


Bullet::Bullet(sf::Vector2f& dir, sf::Vector2f& pos, float velocity, float max_distance, float damage, bool isPiercingArg)
    : Projectile(dir, pos, velocity, max_distance, damage)
{
    isPiercing = isPiercingArg;

}

Bullet::~Bullet() = default;
