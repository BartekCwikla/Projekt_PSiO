#include "meteor_rain.h"
#include "meteor.h"
#include <iostream>
#include <vector>
#include <memory>


MeteorRain::MeteorRain(float cooldown, float damage, int max_meteor) : SuperPower(iconPath, cooldown), damage(damage), max_meteor(max_meteor) {

}

ActionResult MeteorRain::activate(const sf::Vector2f& position) {
    ActionResult result;

    if (!isReady()) {
        return result;
    }

    cooldownClock.restart();
    std::cout << max_meteor << "Max meteor" << std::endl;
    for (int i=0; i < max_meteor; i++) {
        auto m =std::make_unique<Meteor>(damage, (rand()%1500)+500, position);
        result.newMeteors.push_back(std::move(m));
    }

    return result;
}
