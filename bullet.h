#include "projectile.h"

#ifndef BULLET_H
#define BULLET_H



class Bullet : public Projectile {
public:
    Bullet(sf::Vector2f&, sf::Vector2f&, float, float, float, bool isPiercing=false);
    ~Bullet();

    void update() {};
    bool checkColision(const Enemies& colision)  { return false; }
    void move() {}

};



#endif // BULLET_H
