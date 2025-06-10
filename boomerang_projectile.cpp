#include "boomerang_projectile.h"
#include <iostream>


sf::Texture BoomerangProjectile::boomerangTexture;


bool BoomerangProjectile::getExpired() const
{
    return expired;
}

void BoomerangProjectile::setExpired(bool newExpired)
{
    expired = newExpired;
}

void BoomerangProjectile::ensureTextureLoaded() {
    static bool loaded = false;
    if (!loaded) {
        if (!boomerangTexture.loadFromFile("./assets/weapons/boomerang.png")) {
            std::cerr << "Error: could not load boomerang.png\n";
        }
        loaded = true;
    }
}

BoomerangProjectile::BoomerangProjectile(sf::Vector2f direction, sf::Vector2f position, float speed, float maxDistance, float damage)
    : Projectile(direction, position, speed, maxDistance, damage), expired(false) {
    ensureTextureLoaded();
    sprite.setTexture(boomerangTexture);
    sprite.setScale(sf::Vector2f(5,5));
    // Center origin on the sprite
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setPosition(position);
}


sf::Sprite& BoomerangProjectile::getSprite() {
    return sprite;
}


void BoomerangProjectile::move(sf::Time dt, sf::Vector2f playerPos) {
    if (getDistanceTraveled() > getMaxDistance()-50) {
        setIsComingBack(true);
    }

    if (getIsComingBack()) {
        // raw vector computation from boomerang to player
        sf::Vector2f toPlayer = playerPos - getPosition();
        float dist = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
        if (dist < 10.f) {
            setExpired(true);
         }

        // if dist > 0 -> normalize it
        if (dist > 0.f) {
            sf::Vector2f dirUnit = toPlayer / dist;
            float speed = getSpeed();
            sf::Vector2f delta = dirUnit * (speed * dt.asSeconds());
            getBody().setPosition(getPosition() + delta);
            setPosition(getPosition() + delta);
        }
    }
    else {
        Projectile::move(dt);
    }
    sprite.setPosition(getPosition());
}

void BoomerangProjectile::setIsComingBack(bool value) {
    isComingBack = value;
}

bool BoomerangProjectile::getIsComingBack() const {
    return isComingBack;
}

bool BoomerangProjectile::distanceExceeded() const {
    return false;
}

