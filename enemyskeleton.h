#ifndef ENEMYSKELETON_H
#define ENEMYSKELETON_H
#include "enemies.h"
#include "animation.h"
#include <SFML/Graphics.hpp>

class EnemySkeleton: public Enemies {
private:


    Animation animationLeft;
    Animation animationRight;
    bool facingRight = true;
    Animation* currentAnimation = &animationLeft;

public:
    EnemySkeleton(const sf::Vector2f& startPos);
    void render(sf::RenderWindow& window) override;
    void update(sf::Time& dt, const sf::Vector2f& playerPos) override;
    void takeDamage(float dmg) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    void setHP(float hp_) override;
    float getHP() const override;
    void setDamage(float dmg) override;
    float getDamage() const override;
    float getSpeed() const override;
    void setSpeed(float spd) override;
    void setPosition(sf::Vector2f pos) override;
    void applyKnockback(const sf::Vector2f& direction, float strength) override;
    void flashHit(float duration) override;
    void updateKnockFlash(float dt) override;
    void setColor(const sf::Color& color) override;
};

#endif // ENEMYSKELETON_H
