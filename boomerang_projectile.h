#ifndef BOOMERANG_PROJECTILE_H
#define BOOMERANG_PROJECTILE_H

#include "projectile.h"
#include "player.h"

class BoomerangProjectile : public Projectile {
private:
    // This flag is being set after boomerangProjectile comes back to a player and shows, that pointer to this object can be deleted
    bool expired;
    static sf::Texture boomerangTexture;
    float rotationSpeed;
    sf::Sprite sprite;


    static void ensureTextureLoaded();

    bool isComingBack = false;

public:
    BoomerangProjectile(sf::Vector2f direction,
                        sf::Vector2f position,
                        float speed,
                        float maxDistance,
                        float damage);

    sf::Sprite& getSprite();
    void move(sf::Time dt, sf::Vector2f playerPos);
    void update() override {};

    bool distanceExceeded() const override;

    void setIsComingBack(bool value);
    bool getIsComingBack() const;
    bool getExpired() const;
    void setExpired(bool newExpired);
    float getRotationSpeed() const;
    void setRotationSpeed(float newRotationSpeed);
};

#endif // BOOMERANG_PROJECTILE_H
