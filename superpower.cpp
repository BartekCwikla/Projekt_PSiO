#include "superpower.h"
#include <iostream>

sf::Texture SuperPower::getIcon() const
{
    return icon;
}

void SuperPower::setIcon(const sf::Texture &newIcon)
{
    icon = newIcon;
}

SuperPower::SuperPower(std::string iconPath, float cooldown, std::string name) : cooldown(cooldown), name(name) {
    if (!icon.loadFromFile("./assets/weapons/quad_gun.png")){
        std::cerr << "Unable to load meteor texture" << std::endl;
    }
    cooldownClock.restart();
}

std::string SuperPower::getName() const
{
    return name;
}

void SuperPower::setName(const std::string &newName)
{
    name = newName;
}
