#include "fireball_projectile.h"
#include <iostream>



sf::Texture FireballProjectile::getTexture() const
{
    return texture;
}

void FireballProjectile::setTexture(const sf::Texture &newTexture)
{
    texture = newTexture;
}

sf::Sprite FireballProjectile::getSprite() const
{
    return sprite;
}

void FireballProjectile::setSprite(const sf::Sprite &newSprite)
{
    sprite = newSprite;
}

FireballProjectile::FireballProjectile(sf::Vector2f position, sf::Vector2f direction, float damage, float range, float speed) : Projectile(direction, position, speed, range, damage) {
    auto& body = getBody();

    if (!texture.loadFromFile("./assets/SuperPowers/fireball.png")) {
        std::cerr << "Couldn't load meteor texture!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale({5.f, 5.f});

    body.setRadius(150.f);
    float r = body.getRadius();
    body.setOrigin(r, r);
    body.setPosition(position);
    setIsPiercing(true);
}

void FireballProjectile::move(sf::Time dt)
{
    position += velocity * dt.asSeconds();
    float normalised_velocity = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    distance_traveled += normalised_velocity * dt.asSeconds();
    getBody().setPosition(position);
    sprite.setPosition(position);
}
