#include "melee.h"

float Melee::getRange() const
{
    return range;
}

void Melee::setRange(float newRange)
{
    range = newRange;
}

Melee::Melee(float damage, float range): Weapon(), range(range) {
    setDamage(damage);

}
