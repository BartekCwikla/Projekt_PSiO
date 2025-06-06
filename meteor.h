#ifndef METEOR_H
#define METEOR_H

#include "SFML/Graphics.hpp"

class Meteor {
public:
    Meteor(float damage, float initialHeight, sf::Vector2f position);
    float getInitialHeight() const;
    void setInitialHeight(float newInitialHeight);
    float getDistanceTraveled() const;
    void setDistanceTraveled(float newDistanceTraveled);
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &newPosition);
    float getDamage() const;
    void setDamage(float newDamage);
    void move(sf::Time dt);

    float getSpeed() const;
    void setSpeed(float newSpeed);

    float getMaxDistance() const;
    void setMaxDistance(float newMax_distance);

    sf::Sprite getSprite() const;
    void setSprite(const sf::Sprite &newSprite);

    float getExplosionRadius() const;
    void setExplosionRadius(float newExplosionRadius);

    bool getShouldExplode() const;
    void setShouldExplode(bool newShouldExplode);

private:
    float speed;
    bool shouldExplode;
    float explosionRadius;
    float initialHeight;
    float distanceTraveled;
    float max_distance;
    sf::Vector2f position;
    float damage;
    sf::Texture texture;
    sf::Sprite sprite;

};

#endif // METEOR_H
