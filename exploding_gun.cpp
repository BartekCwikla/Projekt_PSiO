#include "exploding_gun.h"
#include "exploding_projectile.h"
#include "gun.h"
#include <iostream>

ExplodingGun::ExplodingGun(float initRange, float initDamage, float initCooldown) : Gun(initRange, initDamage, initCooldown) {
    name="Exploding Gun";
    setVelocity(1500);
    setRange(initRange);
    damage     = initDamage;
    level      = 1;
    setExplosionRange(150.0f);

    if (!texture.loadFromFile("./assets/weapons/exploding_gun.png")){
        std::cerr << "Unable to load double gun texture" << std::endl;
    }
}


std::vector<std::unique_ptr<Projectile>> ExplodingGun::fire(sf::Vector2f position, sf::Vector2f direction) {
    std::vector<std::unique_ptr<Projectile>> shots;

    if (coolDown.getElapsedTime().asSeconds() < cooldownTime)
        return shots;

    coolDown.restart();
    shots.emplace_back(std::make_unique<ExplodingProjectile>(direction, position, getVelocity(), getRange(), getDamage(), getExplosionRange()));
    return shots;
}
