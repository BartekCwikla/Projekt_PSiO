#include "enemies.h"
#include <SFML/Graphics.hpp>

Enemies::Enemies() : hp(0), speed(0) {}


float Enemies::getDamage() const {
    return damage;
}

void Enemies::setDamage(float dmg) {
    damage = dmg;
}
