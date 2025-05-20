#include "bullet.h"


Bullet::Bullet(sf::Vector2f& dir, sf::Vector2f& pos, float velocity, float max_distance, float damage)
    : Projectile(dir, pos, velocity, max_distance, damage)
{
}

Bullet::~Bullet() = default;
