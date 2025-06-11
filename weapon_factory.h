#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "weapon.h"
#include "boomerang.h"
#include "axe.h"
#include "double_gun.h"
#include "quad_gun.h"
#include "exploding_gun.h"
#include "piercing_gun.h"



// This code might be used in the future to implement a weapon choosing screen that is not present for now
class WeaponFactory {
public:
    static std::unique_ptr<Weapon> createRandom();

    static std::unique_ptr<Weapon> createByName(const std::string& name) {
        if (name == "DoubleGun") return std::make_unique<DoubleGun>();
        if (name == "QuadGun") return std::make_unique<QuadGun>();
        if (name == "ExplodingGun") return std::make_unique<ExplodingGun>();
        if (name == "Axe") return std::make_unique<Axe>();
        if (name == "Boomerang") return std::make_unique<Boomerang>();
        if (name == "PiercingGun") return std::make_unique<PiercingGun>();
        return nullptr;
    }

};

#endif // WEAPON_FACTORY_H
