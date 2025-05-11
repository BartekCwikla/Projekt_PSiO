#ifndef ENEMIES_H
#define ENEMIES_H
#include <SFML/Graphics.hpp>

class Enemies
{
private:
    float hp=0.f, speed=0.f;
public:
    Enemies();
    virtual ~Enemies() = default;
    virtual void render(sf::RenderWindow& monsters)=0; //draw enemies
    virtual void update(sf::Time& dt)=0;               // enemies movement, AI logic
    virtual void takeDamage(float dmg)=0;              // enemies damage
    virtual sf::FloatRect getBounds() const = 0;       // collision
    virtual sf::Vector2f getPosition() const = 0;      // actual position

};

#endif // ENEMIES_H
