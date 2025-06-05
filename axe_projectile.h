#ifndef AXE_PROJECTILE_H
#define AXE_PROJECTILE_H

#include "projectile.h"
#include <SFML/Graphics.hpp>

class AxeProjectile : public Projectile {
private:
    static sf::Texture axeTexture;    // shared among all axes
    sf::Sprite sprite;
    float rotationSpeed;
    float explosionRadius;

    // Helper to load texture once
    static void ensureTextureLoaded();

public:
    AxeProjectile(sf::Vector2f direction,
                  sf::Vector2f position,
                  float speed,
                  float maxDistance,
                  float damage,
                  float rotationSpeed,
                  float explosionRadius);

    void update() override;
    bool checkColision(const Enemies& colision) override;

    // Override to return sprite for rendering
    sf::Sprite& getSprite();
    float getRotationSpeed() const { return rotationSpeed; }

    float getExplosionRadius() const;
};

#endif // AXE_PROJECTILE_H
