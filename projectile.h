#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>

class Enemies;

class Projectile
{
private:
    sf::CircleShape body;
    sf::Vector2f velocity;
    float damage;
    sf::Vector2f direction;
    sf::Vector2f position;

public:
    Projectile(sf::Vector2f, sf::Vector2f, float);
    virtual ~Projectile()=default;
    virtual void update()=0;
    virtual bool checkColision(const Enemies& colision)=0;
    virtual void move(sf::Time);
    sf::CircleShape& getBody();
};



#endif // PROJECTILE_H
