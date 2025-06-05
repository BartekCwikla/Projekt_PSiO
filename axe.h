#ifndef AXE_H
#define AXE_H

#include "range.h"

class Axe : public Range {
public:
    Axe();
    ~Axe() override = default;

    std::vector<std::unique_ptr<Projectile>> fire(sf::Vector2f position, sf::Vector2f direction) override;
    void upgrade() override;

private:
    float rotationSpeed = 75.f;
    float aoeRadius = 50.f;
    float cooldownTime = 3.f;
    sf::Clock coolDown;
};

#endif // AXE_H
