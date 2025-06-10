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
    float distance_traveled;
    float max_distance;
    bool isExploding = false;



    // This variable tells whether this projectile has hit the enemy
    bool hit = false;

public:
    Projectile(sf::Vector2f, sf::Vector2f, float, float, float);
    virtual ~Projectile()=default;
    virtual void update()=0;
    virtual bool checkColision(const Enemies& colision)=0;
    virtual void move(sf::Time);
    sf::CircleShape& getBody();

    // Check if the projectile is within allowed range
    bool distanceExceeded() const;

    void setDamage(float);
    float getDamage() const;

    void setDistanceTraveled(float distance);
    float getDistanceTraveled() const;

    void setMaxDistance(float distance);
    float getMaxDistance() const;

    void setHit(bool);
    bool getHit() const;

    sf::Vector2f getPosition() const;

    bool getIsExploding() const;
    void setIsExploding(bool newIsExploding);

    sf::Vector2f getDirection() const;
};



#endif // PROJECTILE_H
