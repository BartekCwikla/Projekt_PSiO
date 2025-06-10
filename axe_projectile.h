#ifndef AXE_PROJECTILE_H
#define AXE_PROJECTILE_H

#include "projectile.h"
#include <SFML/Graphics.hpp>
#include "animation.h"

class AxeProjectile : public Projectile {
private:
    static sf::Texture axeTexture;
    sf::Sprite sprite;
    float rotationSpeed;
    float explosionRadius;


    static void ensureTextureLoaded();

public:
    AxeProjectile(sf::Vector2f direction,
                  sf::Vector2f position,
                  float speed,
                  float maxDistance,
                  float damage,
                  float rotationSpeed,
                  float explosionRadius);

    void update() override {};


    sf::Sprite& getSprite();
    float getRotationSpeed() const { return rotationSpeed; }
    float getExplosionRadius() const;

    void move(sf::Time dt) override;
};

#endif // AXE_PROJECTILE_H
