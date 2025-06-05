#include "quad_gun.h"
#include "bullet.h"
#include <iostream>
#include <cmath>

QuadGun::QuadGun(float initRange, float initDamage, float initCooldown)
    : Gun(initRange, initDamage, initCooldown)
{
    name="Quad Gun";
    setVelocity(2000);
    setRange(initRange);
    damage     = initDamage;
    level      = 1;

    if (!texture.loadFromFile("./assets/weapons/quad_gun.png")){
        std::cerr << "Unable to load double gun texture" << std::endl;
    }

}



std::vector<std::unique_ptr<Projectile>> QuadGun::fire(sf::Vector2f position, sf::Vector2f direction) {
    std::vector<std::unique_ptr<Projectile>> shots;

    if (coolDown.getElapsedTime().asSeconds() < cooldownTime)
        return shots;

    coolDown.restart();

    if (!(std::abs(direction.x) == std::abs(direction.y))) {
        direction = sf::Vector2f(1, 0);
        shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
        direction = sf::Vector2f(0, 1);
        shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
        direction = sf::Vector2f(-1, 0);
        shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
        direction = sf::Vector2f(0, -1);
        shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
    } else {
        direction = sf::Vector2f(1, 1);
        shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
        direction = sf::Vector2f(-1, -1);
        shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
        direction = sf::Vector2f(1, -1);
        shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
        direction = sf::Vector2f(-1, 1);
        shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
    }


    return shots;
}
