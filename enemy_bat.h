#ifndef ENEMY_BAT_H
#define ENEMY_BAT_H
#include "enemies.h"
#include <SFML/Graphics.hpp>
#include "animation.h"
//The bat moves sinusoidally about the selected Y axis
class Enemy_Bat : public Enemies
{
private:
    sf::CircleShape body;
    sf::Vector2f position;
    float constY;
    float speed;
    float hp;

    //Variables that are responsible for the sine wave
    float amplitude;
    float frequency;
    float timePassed;

    Animation animation;
    bool facingRight;


public:
Enemy_Bat( sf::Vector2f startPos);

void render(sf::RenderWindow& window) override;
void update(sf::Time& dt, const sf::Vector2f& playerPos) override;
void takeDamage(float dmg) override;
sf::FloatRect getBounds() const override;
sf::Vector2f getPosition() const override;
float getHP() const override;
};

#endif // ENEMY_BAT_H
