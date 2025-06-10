#include "axe_projectile.h"
#include <iostream>


sf::Texture AxeProjectile::axeTexture;

void AxeProjectile::ensureTextureLoaded() {
    static bool loaded = false;
    if (!loaded) {
        if (!axeTexture.loadFromFile("./assets/weapons/axe.png")) {
            std::cerr << "Error: could not load axe.png\n";
        }
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
    setIsPiercing(true);
    ensureTextureLoaded();
    sprite.setTexture(axeTexture);
    sprite.setScale(sf::Vector2f(5,5));
    // Center origin on the sprite
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setPosition(position);
}



void AxeProjectile::move(sf::Time dt) {
    Projectile::move(dt);
    float angleDelta = rotationSpeed * dt.asSeconds();
    sprite.rotate(angleDelta);
    sprite.setPosition(getPosition());
}



sf::Sprite& AxeProjectile::getSprite() {
    return sprite;
}

float AxeProjectile::getExplosionRadius() const {
    return explosionRadius;
}
