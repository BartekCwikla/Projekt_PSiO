#include "axe.h"
#include "axe_projectile.h"
#include <iostream>

Axe::Axe() {
    name = "Axe";
    setVelocity(600.f);
    setRange(800.f);
    setDamage(20.f);
    setExplosionRange(aoeRadius);
    level = 1;
    if (!texture.loadFromFile("./assets/weapons/axe.png")) {
        std::cerr << "Failed to load axe.png\n";
    }
}

std::vector<std::unique_ptr<Projectile>> Axe::fire(sf::Vector2f position, sf::Vector2f direction) {
    std::vector<std::unique_ptr<Projectile>> shots;

    if (coolDown.getElapsedTime().asSeconds() < cooldownTime)
        return shots;

    coolDown.restart();

    shots.push_back(std::make_unique<AxeProjectile>(
        direction,
        position,
        getVelocity(),
        getRange(),
        getDamage(),
        rotationSpeed,
        getExplosionRange()
        ));

    return shots;
}

void Axe::upgrade() {
    level++;
    setDamage(getDamage() + 5.f);
    cooldownTime = std::max(0.5f, cooldownTime - 0.2f);
    aoeRadius += 10.f;
    setExplosionRange(aoeRadius);
}
