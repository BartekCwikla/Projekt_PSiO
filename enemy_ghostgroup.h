#ifndef ENEMY_GHOSTGROUP_H
#define ENEMY_GHOSTGROUP_H
#include "enemies.h"
#include <SFML/Graphics.hpp>

class Enemy_GhostGroup : public Enemies
{
private:

    sf::RectangleShape body;
    sf::Vector2f direction;
    float constY;
    float speed;
    float hp;

    //Variables that are responsible for the sine wave
    float amplitude;
    float frequency;
    float timePassed;
public:
    Enemy_GhostGroup(const sf::Vector2f& startPos, const sf::Vector2f& dir);

    void render(sf::RenderWindow& window) override;
    void takeDamage(float dmg) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    float getHP() const override;
    void setHP(float& hp_) override;
    void update(sf::Time& dt, const sf::Vector2f& playerPos) override;
};

#endif // ENEMY_GHOSTGROUP_H
