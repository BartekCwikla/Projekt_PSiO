#include "enemy_bat.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Enemy_Bat::Enemy_Bat(sf::Vector2f startPos)
    : position(startPos), constY(startPos.y), speed(300.f),
    hp(20.f), amplitude(60.f), frequency(6.f), timePassed(0.f)
{
    body.setRadius(20.f);
    body.setFillColor(sf::Color::Yellow);
    body.setOrigin(body.getRadius(), body.getRadius());
    body.setPosition(position);
}

void Enemy_Bat::render(sf::RenderWindow& window) {
    body.setPosition(position);
    window.draw(body);
}

void Enemy_Bat::update(sf::Time& time, const sf::Vector2f& player) {
    float dt = time.asSeconds();
    timePassed += dt;
    //X asix is constans
    //Y asix osscilation - sine wave function
    position.y = constY + amplitude * std::sin(frequency * timePassed);
}

//Damage
void Enemy_Bat::takeDamage(float dmg) {
    hp -= dmg;
}

//Getters
sf::FloatRect Enemy_Bat::getBounds() const {
    return body.getGlobalBounds();
}

sf::Vector2f Enemy_Bat::getPosition() const {
    return position;
}

float Enemy_Bat::getHP() const {
    return hp;
}
