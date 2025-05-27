#ifndef MELEE_H
#define MELEE_H

#include "weapon.h"

class Melee : public Weapon {
private:
    float range;

public:
    Melee(float damage, float range);
    float getRange() const;
    void setRange(float newRange);
};

#endif // MELEE_H
