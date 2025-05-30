#include "enemyboss.h"
#include <cmath>
#include <iostream>

EnemyBoss::EnemyBoss(const sf::Vector2f& startPos)
    : animationRight("assets/Boss/WormRight", "WormRight", 9, 0.1f), //Loading boss texture files
    animationLeft("assets/Boss/WormLeft", "WormLeft", 9, 0.1f),
    currentDirection("right"),
    position(startPos)
{
    hp = 1000.f;
    speed = 100.f;
    damage = 5.f;

    animationRight.setPosition(position.x, position.y);
    animationLeft.setPosition(position.x, position.y);

    animationRight.setScale(4.f, 4.f);
    animationLeft.setScale(4.f, 4.f);

    setDamage(damage);
}

void EnemyBoss::render(sf::RenderWindow& window) {
    if (currentDirection == "left") {
        animationLeft.draw(window);
    } else {
        animationRight.draw(window);
    }
}

void EnemyBoss::update(sf::Time& dt, const sf::Vector2f& playerPos) {
    sf::Vector2f dir = playerPos - position;

    //Boss is following the player
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (len > 0.f)
        dir /= len;

    position += dir * speed * dt.asSeconds();

    animationRight.setPosition(position.x, position.y);
    animationLeft.setPosition(position.x, position.y);

    //Changing the animation when boss is moving left or right
    if (dir.x < 0 && currentDirection != "left") {
        currentDirection = "left";
    } else if (dir.x >= 0 && currentDirection != "right") {
        currentDirection = "right";
    }

    if (currentDirection == "left") {
        animationLeft.update(dt.asSeconds());
    } else {
        animationRight.update(dt.asSeconds());
    }
}

void EnemyBoss::takeDamage(float dmg) {
    if (attackCooldown.getElapsedTime().asSeconds() >= attackCooldownTime) {
        hp -= dmg;
        attackCooldown.restart();
    }
}

sf::FloatRect EnemyBoss::getBounds() const {
    return (currentDirection == "left")? animationLeft.getGlobalBounds(): animationRight.getGlobalBounds();

}

sf::Vector2f EnemyBoss::getPosition() const {
    return position;
}

float EnemyBoss::getHP() const {
    return hp;
}

bool EnemyBoss::canAttack() {
    if (attackCooldown.getElapsedTime().asSeconds() >= attackCooldownTime) {
        attackCooldown.restart();
        return true;
    }
    return false;
}


void EnemyBoss::setHP(float& hp_) {
    hp_ = hp;
}
