#include "enemyknight.h"
#include <SFML/Graphics.hpp>
#include <cmath>

EnemyKnight::EnemyKnight(const sf::Vector2f& startPos)
    : hp(200.f), speed(150.f), position(startPos),
    animationLeft("assets/Knight/KnightLeft", "KnightLeft", 8, 0.1f, 1),
    animationRight("assets/Knight/KnightRight", "KnightRight", 8, 0.1f, 1)
{
    setDamage(10.f);
    animationLeft.setScale(2.f, 2.f);
    animationRight.setScale(2.f, 2.f);
    animationLeft.setPosition(position.x, position.y);
    animationRight.setPosition(position.x, position.y);
}

void EnemyKnight::render(sf::RenderWindow& window) {
    if (facingRight)
        animationRight.draw(window);
    else
        animationLeft.draw(window);
}

void EnemyKnight::update(sf::Time& dt, const sf::Vector2f& playerPos) {
    float delta = dt.asSeconds();

    sf::Vector2f dir = playerPos - position;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0)
        dir /= len;

    position += dir * speed * delta;
    facingRight = (dir.x >= 0);

    if (facingRight) {
        animationRight.setPosition(position.x, position.y);
        animationRight.update(delta);
    } else {
        animationLeft.setPosition(position.x, position.y);
        animationLeft.update(delta);
    }
}

void EnemyKnight::takeDamage(float dmg) {
    hp -= dmg;
}

sf::FloatRect EnemyKnight::getBounds() const {
    return facingRight ? animationRight.getGlobalBounds() : animationLeft.getGlobalBounds();
}

sf::Vector2f EnemyKnight::getPosition() const {
    return position;
}

float EnemyKnight::getHP() const {
    return hp;
}


void EnemyKnight::setHP(float& hp_) {
    hp_ = hp;
}
