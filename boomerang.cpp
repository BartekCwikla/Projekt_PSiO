#include "boomerang.h"
#include "boomerang_projectile.h"
#include <iostream>

Boomerang::Boomerang() {
    name = "Boomerang";
    setVelocity(800.f);
    setRange(800.f);
    setDamage(15.f);
    level = 1;
    if (!texture.loadFromFile("./assets/weapons/boomerang.png")) {
        std::cerr << "Failed to load boomerang.png\n";
    }
}

std::vector<std::unique_ptr<Projectile> > Boomerang::fire(sf::Vector2f position, sf::Vector2f direction) {
    std::vector<std::unique_ptr<Projectile>> shots;

    if (coolDown.getElapsedTime().asSeconds() < cooldownTime) {

        return shots;
    }

    coolDown.restart();
    shots.push_back(std::make_unique<BoomerangProjectile>(direction, position, getVelocity(), getRange(), getDamage()));
    return shots;
}

void Boomerang::upgrade() {
    level++;
    setDamage(getDamage() + 5.f);
}



