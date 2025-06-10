#ifndef ENEMYKNIGHT_H
#define ENEMYKNIGHT_H
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "enemies.h"


class EnemyKnight : public Enemies {
private:

    Animation animLeft, animRight;
    Animation* currentAnimation = nullptr;
    bool facingLeft;
public:
    EnemyKnight(const sf::Vector2f& startPos);

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
#endif // ENEMYKNIGHT_H
