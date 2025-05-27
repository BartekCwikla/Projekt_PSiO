#ifndef EXPORB_H
#define EXPORB_H

#include <SFML/Graphics.hpp>

//Exp drops from killed enemies
class ExpOrb {
private:
    sf::CircleShape body;
    float expValue;

public:
    ExpOrb(const sf::Vector2f& pos, float value);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    float getExpValue() const;
};
#endif // EXPORB_H
