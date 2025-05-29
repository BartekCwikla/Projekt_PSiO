#include "weapon.h"


std::string Weapon::getName() const
{
    return name;
}

void Weapon::setName(const std::string &newName)
{
    name = newName;
}

const sf::Texture& Weapon::getTexture() const {
    return texture;
}

Weapon::Weapon()
    : name("Unknown")
    , level(0)
    , damage(0.f)
{ }


void Weapon::setDamage(float new_damage) {
    damage = new_damage;
}

float Weapon::getDamage() const {
    return damage;
}

