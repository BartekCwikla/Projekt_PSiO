#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include <SFML/Graphics.hpp>
#include "animation.h"
#include "enemies.h"

class EnemyBoss : public Enemies {
private:
    Animation animationRight;
    Animation animationLeft;
    std::string currentDirection;
    sf::Vector2f position;

    sf::Clock attackCooldown;
    float attackCooldownTime = 0.5f;

public:
    EnemyBoss(const sf::Vector2f& startPos);
    ~EnemyBoss() override = default;

    void render(sf::RenderWindow& window) override;
    void update(sf::Time& dt, const sf::Vector2f& playerPos) override;
    void takeDamage(float dmg) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    float getHP() const override;
    bool canAttack();
};
#endif // ENEMYBOSS_H

