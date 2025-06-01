#include "enemies.h"
#include <SFML/Graphics.hpp>

Enemies::Enemies(float h, float s, float d) : hp(h), speed(s), damage(d){}


float Enemies::getDamage() const {
    return damage;
}

void Enemies::setDamage(float dmg) {
    damage = dmg;
}
