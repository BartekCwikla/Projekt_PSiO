#include "enemy_demon.h"
#include <cmath>

Enemy_Demon::Enemy_Demon(const sf::Vector2f& startPos) {
    bodyDemon.setSize(sf::Vector2f(40.f, 40.f));
    bodyDemon.setFillColor(sf::Color::Red);
    bodyDemon.setPosition(startPos);

    hp = 10.f;
    speed = 100.f;
    setDamage(10.0f);
}

void Enemy_Demon::render(sf::RenderWindow& window) {
    window.draw(bodyDemon);
}

void Enemy_Demon::update(sf::Time& dt, const sf::Vector2f& playerPos) {
    sf::Vector2f dir = playerPos - bodyDemon.getPosition();
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0)
        dir /= len;

    bodyDemon.move(dir * speed * dt.asSeconds());
}

void Enemy_Demon::takeDamage(float dmg) {
    hp -= dmg;
}

sf::FloatRect Enemy_Demon::getBounds() const {
    return bodyDemon.getGlobalBounds();
}

sf::Vector2f Enemy_Demon::getPosition() const {
    return bodyDemon.getPosition();
}

float Enemy_Demon::getHP() const {
    return hp;
}

