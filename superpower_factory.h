#ifndef SUPERPOWER_FACTORY_H
#define SUPERPOWER_FACTORY_H

#include "superpower.h"

class SuperPowerFactory {
public:
    static std::unique_ptr<SuperPower> createRandom();
};

#endif // SUPERPOWER_FACTORY_H
