#include "axe_projectile.h"
#include <iostream>

// Define the static texture
sf::Texture AxeProjectile::axeTexture;

void AxeProjectile::ensureTextureLoaded() {
    static bool loaded = false;
    if (!loaded) {
        if (!axeTexture.loadFromFile("./assets/weapons/axe.png")) {
            std::cerr << "Error: could not load axe.png\n";
        }
        // Center the origin so rotation is around center
        loaded = true;
    }
}

AxeProjectile::AxeProjectile(sf::Vector2f direction,
                             sf::Vector2f position,
                             float speed,
                             float maxDistance,
                             float damage,
                             float rotationSpeed,
                             float explosionRadius)
    : Projectile(direction, position, speed, maxDistance, damage)
    , rotationSpeed(rotationSpeed)
    , explosionRadius(explosionRadius)
{
    ensureTextureLoaded();
    sprite.setTexture(axeTexture);
    // Center origin on the sprite
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setPosition(position);
}

void AxeProjectile::update() {
    // Move as base class does
    Projectile::move(sf::seconds(1.f / 60.f));  // or pass your actual dt
    // Spin
    sprite.rotate(rotationSpeed);
    // Sync position
    sprite.setPosition(getPosition());
}

bool AxeProjectile::checkColision(const Enemies& colision) {
    // Your AoE logic here...
    return false;
}

sf::Sprite& AxeProjectile::getSprite() {
    return sprite;
}

float AxeProjectile::getExplosionRadius() const {
    return explosionRadius;
}
