#include "exploding_projectile.h"


ExplodingProjectile::ExplodingProjectile(sf::Vector2f dir, sf::Vector2f initial_position, float speed, float max_distance, float damage, float explosion_radius) : Projectile(dir, initial_position, speed, max_distance, damage), explosionRadius(explosion_radius) {
    setIsExploding(true);
}



