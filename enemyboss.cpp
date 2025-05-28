#include "enemyboss.h"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

EnemyBoss:: EnemyBoss(const sf::Vector2f& startPos)
    : hp(1050.f), speed(50.f), timePassed(0.f)
{
    if (!texture.loadFromFile("./assets/Boss/boss_move_left.png") && !texture.loadFromFile("./assets/Boss/boss_move_right.png")) {
        std::cerr << "Failed to load boss texture!\n";
    }
    body.setTexture(texture);
    body.setPosition(startPos);
    body.setScale(2.f, 2.f); // boss is huge
}


void EnemyBoss::render(sf::RenderWindow& window) {
    window.draw(body);
}

void EnemyBoss::update(sf::Time& dt, const sf::Vector2f& playerPos) {
    sf::Vector2f dir = playerPos - body.getPosition();
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0)
        dir /= len;

    body.move(dir * speed * dt.asSeconds());
}









//Damage
void EnemyBoss::takeDamage(float dmg) {
    hp -= dmg;
}

//Getters
sf::FloatRect EnemyBoss::getBounds() const {
    return body.getGlobalBounds();
}

sf::Vector2f EnemyBoss::getPosition() const {
    return body.getPosition();
}

float EnemyBoss::getHP() const {
    return hp;
}
