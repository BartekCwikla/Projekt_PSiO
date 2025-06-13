#include "weapon_factory.h"

std::unique_ptr<Weapon> WeaponFactory::createRandom() {
    std::vector<std::unique_ptr<Weapon>> weapon_arr;

    switch (std::rand() % 5) {
    case 0: return std::make_unique<Boomerang>();
    case 1: return std::make_unique<Axe>();
    case 2: return std::make_unique<PiercingGun>();
    case 3: return std::make_unique<ExplodingGun>();
    case 4: return std::make_unique<DoubleGun>();
    case 5: return std::make_unique<QuadGun>();
    }
    return nullptr;
}
