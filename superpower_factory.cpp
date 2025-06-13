#include "superpower_factory.h"
#include "meteor_rain.h"



// Not being used right now. This might be helpful while creating a superpower choosing screen.
std::unique_ptr<SuperPower> SuperPowerFactory::createRandom() {
    switch (std::rand() % 1) {
    case 0: return std::make_unique<MeteorRain>();
    }
    return nullptr;
}
