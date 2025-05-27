#include "weapon.h"
#include "projectile.h"


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

