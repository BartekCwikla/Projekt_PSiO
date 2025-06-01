#ifndef ENEMYKNIGHT_H
#define ENEMYKNIGHT_H
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "enemies.h"


class EnemyKnight : public Enemies {
private:

    sf::Vector2f position;
    Animation animationLeft;
    Animation animationRight;
    bool facingRight = true;

public:
    EnemyKnight(const sf::Vector2f& startPos);
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
};
#endif // ENEMYKNIGHT_H
