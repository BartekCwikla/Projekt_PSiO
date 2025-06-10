#ifndef ENEMY_GHOSTGROUP_H
#define ENEMY_GHOSTGROUP_H
#include "enemies.h"
#include "animation.h"
#include <SFML/Graphics.hpp>

class Enemy_GhostGroup : public Enemies
{
private:


    sf::Vector2f direction;
    float constY;

    //Variables that are responsible for the sine wave
    float amplitude;
    float frequency;
    float timePassed;
    Animation animationLeft;
    Animation animationRight;
    Animation* currentAnimation = nullptr;
    bool facingLeft;


public:
    Enemy_GhostGroup(const sf::Vector2f& startPos, const sf::Vector2f& dir);

    void render(sf::RenderWindow& window) override;
    void takeDamage(float dmg) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    float getHP() const override;
    void setHP(float hp_) override;
    float getDamage() const override;
    void setDamage(float dmg) override;
    float getSpeed() const override;
    void setSpeed(float spd) override;
    void setPosition(sf::Vector2f pos) override;
    void update(sf::Time& dt, const sf::Vector2f& playerPos) override;

    void applyKnockback(const sf::Vector2f& direction, float strength) override;
    void flashHit(float duration) override;
    void updateKnockFlash(float dt) override;
    void setColor(const sf::Color& color) override;
};

#endif // ENEMY_GHOSTGROUP_H
