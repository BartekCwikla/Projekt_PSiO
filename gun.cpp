#include "gun.h"
#include "bullet.h"
#include "exploding_projectile.h"


Gun::Gun(float initRange, float initDamage, float initCooldown)
    : cooldownTime(initCooldown)
{
    setVelocity(1000);
    setRange(initRange);
    damage     = initDamage;
    level      = 1;

}

std::vector<std::unique_ptr<Projectile>> Gun::fire(sf::Vector2f position, sf::Vector2f direction) {
    std::vector<std::unique_ptr<Projectile>> shots;

    if (coolDown.getElapsedTime().asSeconds() < cooldownTime)
        return shots;

    coolDown.restart();

    // shots.push_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
    shots.push_back(std::make_unique<ExplodingProjectile>(direction, position, getVelocity(), getRange(), getDamage(), 200.0f));

    return shots;
}

void Gun::upgrade()
{
    level++;
    damage       += 2.f;
    cooldownTime  = std::max(0.1f, cooldownTime - 0.05f);
}
