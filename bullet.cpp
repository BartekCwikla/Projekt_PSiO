#include "bullet.h"


Bullet::Bullet(sf::Vector2f& dir, sf::Vector2f& pos, float velocity)
    : Projectile(dir, pos, velocity)
{
}

Bullet::~Bullet() = default;
