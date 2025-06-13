#ifndef FIREBALL_PROJECTILE_H
#define FIREBALL_PROJECTILE_H

#include "projectile.h"

class FireballProjectile : public Projectile {
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    FireballProjectile(sf::Vector2f position, sf::Vector2f direction, float damage, float range, float speed);
    void update() {};
    void move(sf::Time dt);
    sf::Texture getTexture() const;
    void setTexture(const sf::Texture &newTexture);
    sf::Sprite getSprite() const;
    void setSprite(const sf::Sprite &newSprite);
};

#endif // FIREBALL_PROJECTILE_H
