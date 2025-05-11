#ifndef PROJECTILES_H
#define PROJECTILES_H
#include <SFML/Graphics.hpp>

class Enemies;

class Projectiles
{
private:
    sf::CircleShape bullet;
    sf::Vector2f velocity;
    float damage;

public:
    Projectiles();
    virtual ~Projectiles()=default;
    virtual void update()=0;
    virtual bool checkColision(const Enemies& colision)=0;
};

#endif // PROJECTILES_H
