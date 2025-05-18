#include "projectile.h"

Projectile::Projectile(sf::Vector2f dir, sf::Vector2f initial_position, float speed) : direction(dir), position(initial_position) {
    body.setRadius(5.f);
    body.setOrigin(5.f, 5.f);
    body.setPosition(position);
    body.setFillColor(sf::Color::White);

    velocity = direction * speed;
}



void Projectile::move(sf::Time dt) {
    position += velocity * dt.asSeconds();
    body.setPosition(position);
}


sf::CircleShape& Projectile::getBody() {
    return body;
}

