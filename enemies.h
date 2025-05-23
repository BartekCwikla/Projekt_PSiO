#ifndef ENEMIES_H
#define ENEMIES_H
#include <SFML/Graphics.hpp>

class Enemies
{
private:
    float hp, speed;
public:
    Enemies();
    virtual ~Enemies() = default;
    virtual void render(sf::RenderWindow& monsters)=0; //draw enemies
    virtual void update(sf::Time& dt, const sf::Vector2f& playerPos) = 0;   // enemies movement, AI logic
    virtual void takeDamage(float dmg)=0;              // enemies damage
    virtual sf::FloatRect getBounds() const = 0;       // collision
    virtual sf::Vector2f getPosition() const = 0;      // actual position
    virtual float getHP() const = 0;

};

#endif // ENEMIES_H
