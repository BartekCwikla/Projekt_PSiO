#ifndef ENEMIES_H
#define ENEMIES_H
#include <SFML/Graphics.hpp>
#include "animation.h"

class Enemies
{
protected:
    float hp, speed, damage;
    sf::Vector2f position;
    sf::Vector2f knockbackVelocity;
    float knockTimer=0.f;
    sf::Color originalColor = sf::Color::White;
    bool isFlashActive = false;
    float FlashTimer = 0.f;
public:
    Enemies(float h, float s, float d, sf::Vector2f p);
    virtual ~Enemies() = default;
    virtual void render(sf::RenderWindow& monsters)=0; //draw enemies
    virtual void update(sf::Time& dt, const sf::Vector2f& playerPos) = 0;   // enemies movement, AI logic
    virtual void takeDamage(float dmg)=0;              // enemies damage
    virtual sf::FloatRect getBounds() const = 0;       // collision
    virtual sf::Vector2f getPosition() const = 0;      // actual position
    virtual float getHP() const = 0;
    virtual void setHP(float hp_) = 0;
    virtual float getDamage() const = 0;
    virtual void setDamage(float dmg)=0;
    virtual float getSpeed() const = 0;
    virtual void setSpeed(float spd) =0;
    virtual void setPosition(sf::Vector2f pos) =0;

    virtual void applyKnockback(const sf::Vector2f& direction, float strength)=0; //setting velocity and time duration of knockback
    virtual void flashHit(float duration)=0;                                      // activate flash effect after hit the enemy
    virtual void updateKnockFlash(float dt)=0;                                    // manage movement of enemies and resets the color
    virtual void setColor(const sf::Color& color)=0;                              // setting white color to the actual animation frame



};

#endif // ENEMIES_H
