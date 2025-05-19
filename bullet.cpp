#include "bullet.h"


Bullet::Bullet(sf::Vector2f& dir, sf::Vector2f& pos, float velocity, float max_distance)
    : Projectile(dir, pos, velocity, max_distance)
{
}

Bullet::~Bullet() = default;
