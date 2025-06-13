#include "bullet.h"


Bullet::Bullet(sf::Vector2f& dir, sf::Vector2f& pos, float velocity, float max_distance, float damage, bool isPiercingArg)
    : Projectile(dir, pos, velocity, max_distance, damage)
{
    isPiercing = isPiercingArg;
    sound.loadSoundEffect("gun", "./assets/Sounds/Sounds/gun.wav", 35.f, false);
    sound.playSoundEffect("gun");
}

Bullet::~Bullet() = default;
