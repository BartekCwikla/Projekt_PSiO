#ifndef METEOR_RAIN_H
#define METEOR_RAIN_H

#include "superpower.h"
#include <memory>
#include "meteor.h"

class MeteorRain : public SuperPower {
private:
    float damage;
    std::string name;
    std::string iconPath = "./assets/SuperPowers/meteor.png";
    int max_meteor;

public:
    MeteorRain(float cooldown = 3.f, float damage = 100.f, int max_meteor = 10);
    ActionResult activate(const sf::Vector2f& position);
};


#endif // METEOR_RAIN_H
