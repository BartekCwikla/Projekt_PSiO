#ifndef ENEMY_DEMON_H
#define ENEMY_DEMON_H
#include "enemies.h"
#include<SFML/Graphics.hpp>


class Enemy_Demon : public Enemies
{
private:
    sf::RectangleShape bodyDemon;
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

    void update(sf::Time& dt, const sf::Vector2f& playerPos) override;
};

#endif // ENEMY_DEMON_H
