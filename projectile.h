#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <cmath>
#include <SFML/Graphics.hpp>

class Enemies;

class Projectile
{
private:
    sf::CircleShape body;
    float damage;
    sf::Vector2f direction;
    sf::Vector2f position;
    float distance_traveled;
    float max_distance;
    bool isExploding = false;



    // This variable tells whether this projectile has hit the enemy
    bool hit = false;

protected:
    bool isPiercing = false;
    sf::Vector2f velocity;
    float speed = 5.f;


public:
    Projectile(sf::Vector2f, sf::Vector2f, float, float, float);
    virtual ~Projectile()=default;
    virtual void update()=0;
    virtual bool checkColision(const Enemies& colision) {return false;};
    virtual void move(sf::Time dt) {
        position += velocity * dt.asSeconds();
        float normalised_velocity = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        distance_traveled += normalised_velocity * dt.asSeconds();
        body.setPosition(position);
    }
    sf::CircleShape& getBody();

    // Check if the projectile is within allowed range
    virtual bool distanceExceeded() const;

    void setDamage(float);
    float getDamage() const;

    void setDistanceTraveled(float distance);
    float getDistanceTraveled() const;

    void setMaxDistance(float distance);
    float getMaxDistance() const;

    void setHit(bool);
    bool getHit() const;

    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);

    bool getIsExploding() const;
    void setIsExploding(bool newIsExploding);

    sf::Vector2f getDirection() const;

    bool getIsPiercing() const;
    void setIsPiercing(bool newIsPiercing);
    float getSpeed() const;
    void setSpeed(float newSpeed);

};



#endif // PROJECTILE_H
