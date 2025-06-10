#include "projectile.h"
#include <cmath>





Projectile::Projectile(sf::Vector2f dir, sf::Vector2f initial_position, float speed, float max_distance, float damage)
    : direction(dir), position(initial_position), max_distance(max_distance), damage(damage) {
    //direction vector normalization in Projectile class constructor
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0.f)
        direction = dir / len;
    else
        direction = sf::Vector2f(0.f, 0.f);

    body.setRadius(5.f);
    body.setOrigin(5.f, 5.f);
    body.setPosition(position);
    body.setFillColor(sf::Color::White);
    setDistanceTraveled(0.f);
    velocity = direction * speed;
}



void Projectile::move(sf::Time dt) {
    position += velocity * dt.asSeconds();
    float normalised_velocity = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
    distance_traveled += normalised_velocity * dt.asSeconds();
    body.setPosition(position);
}


sf::CircleShape& Projectile::getBody() {
    return body;
}


void Projectile::setDamage(float new_damage) {
    damage = new_damage;
}

float Projectile::getDamage() const {
    return damage;
}


void Projectile::setDistanceTraveled(float distance) {
    distance_traveled = distance;
}

float Projectile::getDistanceTraveled() const {
    return distance_traveled;
}


void Projectile::setMaxDistance(float distance) {
    max_distance = distance;
}

float Projectile::getMaxDistance() const {
    return max_distance;
}


bool Projectile::distanceExceeded() const {
    return (this->getDistanceTraveled() > this->getMaxDistance());
}


void Projectile::setHit(bool isHit) {
    hit = isHit;
}

bool Projectile::getHit() const {
    return hit;
}


sf::Vector2f Projectile::getPosition() const
{
    return position;
}

bool Projectile::getIsExploding() const
{
    return isExploding;
}

void Projectile::setIsExploding(bool newIsExploding)
{
    isExploding = newIsExploding;
}

sf::Vector2f Projectile::getDirection() const{
    return direction;
}
