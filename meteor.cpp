#include "meteor.h"
#include <iostream>

Meteor::Meteor(float damage, float initialHeight, sf::Vector2f position)
    : initialHeight(initialHeight), damage(damage), shouldExplode(false), distanceTraveled(0.f), explosionRadius(200.f)
{
    speed = (rand()%500)+300;


    if (!texture.loadFromFile("./assets/SuperPowers/meteor.png")) {
        std::cerr << "Couldn't load meteor texture!" << std::endl;
    }
    setMaxDistance(500.f);
    sprite.setTexture(texture);
    sf::Vector2f newPosition = {position.x + (rand() % 2001) - 1000, position.y + (rand() % 800) - 1000};
    sprite.setPosition(newPosition);
    setPosition(newPosition);
    sprite.setScale({5.f, 5.f});
}

float Meteor::getInitialHeight() const
{
    return initialHeight;
}

void Meteor::setInitialHeight(float newInitialHeight)
{
    initialHeight = newInitialHeight;
}

float Meteor::getDistanceTraveled() const
{
    return distanceTraveled;
}

void Meteor::setDistanceTraveled(float newDistanceTraveled)
{
    distanceTraveled = newDistanceTraveled;
}

sf::Vector2f Meteor::getPosition() const
{
    return position;
}

void Meteor::setPosition(const sf::Vector2f &newPosition)
{
    position = newPosition;
}

float Meteor::getDamage() const
{
    return damage;
}

void Meteor::setDamage(float newDamage)
{
    damage = newDamage;
}

void Meteor::move(sf::Time dt) {
    if (getDistanceTraveled() > getMaxDistance()) {
        shouldExplode = true;
        return;
    }

    float dy = speed * dt.asSeconds();
    position.y += dy;
    distanceTraveled += dy;
    sprite.setPosition(position);


}

float Meteor::getSpeed() const
{
    return speed;
}

void Meteor::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

float Meteor::getMaxDistance() const
{
    return max_distance;
}

void Meteor::setMaxDistance(float newMaxDistance)
{
    max_distance = newMaxDistance;
}

sf::Sprite Meteor::getSprite() const
{
    return sprite;
}

void Meteor::setSprite(const sf::Sprite &newSprite)
{
    sprite = newSprite;
}

float Meteor::getExplosionRadius() const
{
    return explosionRadius;
}

void Meteor::setExplosionRadius(float newExplosionRadius)
{
    explosionRadius = newExplosionRadius;
}

bool Meteor::getShouldExplode() const
{
    return shouldExplode;
}

void Meteor::setShouldExplode(bool newShouldExplode)
{
    shouldExplode = newShouldExplode;
}
