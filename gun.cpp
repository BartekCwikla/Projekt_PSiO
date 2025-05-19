#include "gun.h"
#include "bullet.h"



Gun::Gun(float initRange, float initDamage, float initCooldown)
    : cooldownTime(initCooldown)
{
    setVelocity(1000);
    setRange(initRange);
    damage     = initDamage;
    level      = 1;

}

std::unique_ptr<Projectile> Gun::fire(sf::Vector2f position, sf::Vector2f direction)
{
    if (coolDown.getElapsedTime().asSeconds() < cooldownTime)
        return nullptr;

    coolDown.restart();

    return std::make_unique<Bullet>(direction, position, getVelocity(), getRange());
}

void Gun::upgrade()
{
    level++;
    damage       += 2.f;
    cooldownTime  = std::max(0.1f, cooldownTime - 0.05f);
}
