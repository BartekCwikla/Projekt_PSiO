#ifndef ENEMY_GHOSTGROUP_H
#define ENEMY_GHOSTGROUP_H
#include "enemies.h"
#include <SFML/Graphics.hpp>

class Enemy_GhostGroup : public Enemies
{
private:
    float hp, speed;
    sf::RectangleShape body;
public:
    Enemy_GhostGroup(const sf::Vector2f& startPos);

    void render(sf::RenderWindow& window) override;
    void takeDamage(float dmg) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    float getHP() const override;
    void update(sf::Time& dt, const sf::Vector2f& playerPos) override;
};

#endif // ENEMY_GHOSTGROUP_H
