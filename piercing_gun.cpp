#include "piercing_gun.h"
#include <iostream>
#include "bullet.h"

PiercingGun::PiercingGun(float initRange, float initDamage, float initCooldown) {
    name="Piercing Gun";
    setVelocity(1500);
    setRange(initRange);
    damage     = initDamage;
    level      = 1;
    setIsPiercing(true);

    if (!texture.loadFromFile("./assets/weapons/piercing_gun.png")){
        std::cerr << "Unable to load double gun texture" << std::endl;
    }
}

std::vector<std::unique_ptr<Projectile>> PiercingGun::fire(sf::Vector2f position, sf::Vector2f direction) {
    std::vector<std::unique_ptr<Projectile>> shots;

    if (coolDown.getElapsedTime().asSeconds() < cooldownTime)
        return shots;

    coolDown.restart();
    shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage(), true));
    return shots;
}
