#ifndef ENEMYVORTEX_H
#define ENEMYVORTEX_H

#include "enemies.h"
#include "animation.h"
#include <SFML/Graphics.hpp>

class EnemyVortex : public Enemies {
private:



    sf::Vector2f velocity;
    float angle;
    float angleSpeed; //angle/seconds
    Animation vortex;
    float phaseDifference;
    Animation* currentAnimation = nullptr;

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
    void setPosition(sf::Vector2f pos) override;
     void applyKnockback(const sf::Vector2f& direction, float strength) override;
    void flashHit(float duration) override;
   void updateKnockFlash(float dt) override;

  void setColor(const sf::Color& color) override;
};

#endif // ENEMYVORTEX_H
