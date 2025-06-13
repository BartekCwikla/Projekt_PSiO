#ifndef EXPORB_H
#define EXPORB_H
#include "animation.h"

#include <SFML/Graphics.hpp>

//Exp drops from killed enemies
class ExpOrb {
private:
    Animation greenOrb;
    sf::CircleShape body;
    float expValue;

public:
    ExpOrb(const sf::Vector2f& pos, float value);
    void render(sf::RenderWindow& window, float dt);
    sf::FloatRect getBounds() const;
    float getExpValue() const;
};
#endif // EXPORB_H
