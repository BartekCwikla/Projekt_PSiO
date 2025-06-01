#ifndef ENEMYVORTEX_H
#define ENEMYVORTEX_H

#include "enemies.h"
#include "animation.h"
#include <SFML/Graphics.hpp>

class EnemyVortex : public Enemies {
private:


    sf::Vector2f position;
    sf::Vector2f velocity;
    float angle;
    float angleSpeed; //angle/seconds
    Animation vortex;
    float phaseDifference;

public:
    EnemyVortex(const sf::Vector2f& startPos);
    sf::Vector2f recoilForce(const sf::Vector2f& playerPos) const;
    void update(sf::Time& dt, const sf::Vector2f& playerPos) override;
    void render(sf::RenderWindow& window) override;
    void takeDamage(float dmg) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    void setHP(float hp_) override;
    float getHP() const override;
    float getDamage() const override;
    void setDamage(float dmg) override;
    float getSpeed() const override;
    void setSpeed(float spd) override;
};

#endif // ENEMYVORTEX_H
