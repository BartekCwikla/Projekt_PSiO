#include "superpower_factory.h"
#include "meteor_rain.h"


std::unique_ptr<SuperPower> SuperPowerFactory::createRandom() {
    switch (std::rand() % 1) {
    case 0: return std::make_unique<MeteorRain>();
    }
}
