#include "double_gun.h"
#include "bullet.h"
#include <iostream>

DoubleGun::DoubleGun(float initRange, float initDamage, float initCooldown)
    : Gun(initRange, initDamage, initCooldown)
{
    name="Double Gun";
    setVelocity(2000);
    setRange(initRange);
    damage     = initDamage;
    level      = 1;

    if (!texture.loadFromFile("./assets/weapons/double_gun.png")){
        std::cerr << "Unable to load double gun texture" << std::endl;
    }

}



std::vector<std::unique_ptr<Projectile>> DoubleGun::fire(sf::Vector2f position, sf::Vector2f direction) {
    std::vector<std::unique_ptr<Projectile>> shots;

    if (coolDown.getElapsedTime().asSeconds() < cooldownTime)
        return shots;

    coolDown.restart();

    // This line creates a reversed direction for the second bullet
    sf::Vector2f reversed(-direction.x, -direction.y);
    shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
    shots.emplace_back(std::make_unique<Bullet>(reversed, position, getVelocity(), getRange(), getDamage()));
    return shots;
}
