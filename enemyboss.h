#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H
#include "enemies.h"
#include <SFML/Graphics.hpp>

class EnemyBoss : public Enemies
{
private:
    float hp, speed;
    sf::Texture texture;
    sf::Sprite body;
    float timePassed;
public:
    EnemyBoss(const sf::Vector2f& startPos);

    void render(sf::RenderWindow& window) override;
    void takeDamage(float dmg) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    float getHP() const override;
    void update(sf::Time& dt, const sf::Vector2f& playerPos) override;
};

#endif // ENEMYBOSS_H
