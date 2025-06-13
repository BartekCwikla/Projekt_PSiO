#ifndef SUPERPOWER_H
#define SUPERPOWER_H

#include "ActionResult.h"

class SuperPower {
private:

    std::string name = "SuperPower";
    float cooldown;

protected:
    sf::Clock  cooldownClock;
   sf::Texture icon;

public:
   SuperPower(std::string iconPath, float cooldown, std::string name = "SuperPower");
    virtual ActionResult activate(const sf::Vector2f& position) {};
    virtual ActionResult activate(const sf::Vector2f& position,
                                  const sf::Vector2f& direction) {};
    std::string getName() const;
    void setName(const std::string &newName);
    sf::Texture getIcon() const;
    void setIcon(const sf::Texture &newIcon);

    bool isReady() const {
        return cooldownClock.getElapsedTime().asSeconds() >= cooldown;
    }

    void resetCooldown() {
        cooldownClock.restart();
    }
};

#endif // SUPERPOWER_H
