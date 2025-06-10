#include "enemies.h"
#include <SFML/Graphics.hpp>

Enemies::Enemies(float h, float s, float d, sf::Vector2f p) : hp(h), speed(s), damage(d), position(p){}


float Enemies::getDamage() const {
    return damage;
}

void Enemies::setDamage(float dmg) {
    damage = dmg;
}

