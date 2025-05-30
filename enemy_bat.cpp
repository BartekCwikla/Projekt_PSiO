

#include "enemy_bat.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Enemy_Bat::Enemy_Bat(sf::Vector2f startPos)
    : position(startPos), constY(startPos.y), speed(300.f),
    hp(35.f), amplitude(60.f), frequency(6.f), timePassed(0.f),
    animation("./assets/Bat", "Bat", 4, 0.14f, 1)
{
    setDamage(5.0f);
    body.setRadius(20.f);
    animation.setScale(1.f, 1.f);
    animation.setPosition(position.x, position.y);
}

void Enemy_Bat::render(sf::RenderWindow& window) {
    animation.draw(window);
}

void Enemy_Bat::update(sf::Time& time, const sf::Vector2f& player) {
    float dt = time.asSeconds();
    timePassed += dt;
    //X asix is constans
    //Y asix osscilation - sine wave function
    position.y = constY + amplitude * std::sin(frequency * timePassed);

    animation.setPosition(position.x, position.y);
    animation.update(dt);
}

//Damage
void Enemy_Bat::takeDamage(float dmg) {
    hp -= dmg;
}

//Getters
sf::FloatRect Enemy_Bat::getBounds() const {
    return animation.getGlobalBounds();
}

sf::Vector2f Enemy_Bat::getPosition() const {
    return position;
}

float Enemy_Bat::getHP() const {
    return hp;
}
/*
#include "enemy_bat.h"
#include <cmath>

Enemy_Bat::Enemy_Bat(sf::Vector2f startPos)
    : position(startPos), constY(startPos.y), speed(300.f),
    hp(35.f), amplitude(60.f), frequency(6.f), timePassed(0.f),
    animation("./assets/Bat", "Bat", 4, 0.12f, 1)
{
    setDamage(10.0f);
    animation.setScale(1.f, 1.f);
    animation.setPosition(position.x, position.y);
}

void Enemy_Bat::render(sf::RenderWindow& window) {
    animation.draw(window);
}

void Enemy_Bat::update(sf::Time& time, const sf::Vector2f&) {
    float dt = time.asSeconds();
    timePassed += dt;

    // aktualizacja pozycji Y sinusoidalnie (oscylacja)
    position.y = constY + amplitude * std::sin(frequency * timePassed);

    animation.setPosition(position.x, position.y);
    animation.update(dt);
}

void Enemy_Bat::takeDamage(float dmg) {
    hp -= dmg;
}

sf::FloatRect Enemy_Bat::getBounds() const {
    return animation.getGlobalBounds();
}

sf::Vector2f Enemy_Bat::getPosition() const {
    return position;
}

float Enemy_Bat::getHP() const {
    return hp;
}
*/
