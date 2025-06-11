#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "weapon.h"
#include "boomerang.h"
#include "axe.h"
#include "double_gun.h"
#include "quad_gun.h"
#include "exploding_gun.h"
#include "piercing_gun.h"

class WeaponFactory {
public:
    static std::unique_ptr<Weapon> createRandom();

};

#endif // WEAPON_FACTORY_H
