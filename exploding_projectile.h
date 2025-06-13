#ifndef EXPLODING_PROJECTILE_H
#define EXPLODING_PROJECTILE_H

#include "projectile.h"

class ExplodingProjectile : public Projectile {
private:
    float explosionRadius;

public:
    ExplodingProjectile(sf::Vector2f dir, sf::Vector2f initial_position, float speed, float max_distance, float damage, float explosion_radius);

    void setExplosionRadius(float newExplosionRadius) {
        explosionRadius = newExplosionRadius;
    }

    float getExplosionRadius() const {
        return explosionRadius;
    }

    void update() override {}
    void move() {}
};

#endif // EXPLODING_PROJECTILE_H
