#ifndef BOOMERANG_H
#define BOOMERANG_H

#include "range.h"

class Boomerang : public Range {
public:
    Boomerang();
    ~Boomerang() override = default;
    void upgrade() override;
    std::vector<std::unique_ptr<Projectile>> fire(sf::Vector2f position, sf::Vector2f direction);
private:
    float cooldownTime = 1.f;
};


#endif // BOOMERANG_H
