 #ifndef ENEMY_BAT_H
#define ENEMY_BAT_H
#include "enemies.h"
#include <SFML/Graphics.hpp>
#include "animation.h"
//The bat moves sinusoidally about the selected Y axis
class Enemy_Bat : public Enemies
{
private:

    float constY;
        //Variables that are responsible for the sine wave
    float amplitude;
    float frequency;
    float timePassed;

    Animation animation;
    Animation* currentAnimation = nullptr;
    bool facingRight;


public:
Enemy_Bat( sf::Vector2f startPos);

void render(sf::RenderWindow& window) override;
void update(sf::Time& dt, const sf::Vector2f& playerPos) override;
void takeDamage(float dmg) override;
sf::FloatRect getBounds() const override;
sf::Vector2f getPosition() const override;
float getHP() const override;
void setHP(float hp_) override;
void setDamage(float dmg) override;
float getDamage() const override;
float getSpeed() const override;
void setSpeed(float spd) override;
void setPosition(sf::Vector2f pos) override;

void applyKnockback(const sf::Vector2f& direction, float strength) override;
void flashHit(float duration) override;
void updateKnockFlash(float dt) override;
void setColor(const sf::Color& color) override;

};

#endif // ENEMY_BAT_H
