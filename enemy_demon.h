#ifndef ENEMY_DEMON_H
#define ENEMY_DEMON_H
#include "enemies.h"
#include "animation.h"
#include<SFML/Graphics.hpp>


class Enemy_Demon : public Enemies
{
private:

    Animation animLeft, animRight;
    bool facingLeft;
    Animation* currentAnimation = nullptr;
public:
    Enemy_Demon(const sf::Vector2f& startPos);

    void render(sf::RenderWindow& window) override;
    void takeDamage(float dmg) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    float getHP() const override;
    void setHP(float hp_) override;
    float getSpeed() const override;
    void setSpeed(float spd) override;
    float getDamage() const override;
    void setDamage(float dmg) override;
    void setPosition(sf::Vector2f pos) override;
    void update(sf::Time& dt, const sf::Vector2f& playerPos) override;

    void applyKnockback(const sf::Vector2f& direction, float strength) override;
    void flashHit(float duration) override;
    void updateKnockFlash(float dt) override;
    void setColor(const sf::Color& color) override;
};

#endif // ENEMY_DEMON_H
