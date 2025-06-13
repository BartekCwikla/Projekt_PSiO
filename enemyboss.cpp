#include "enemyboss.h"
#include <cmath>
#include <iostream>

EnemyBoss::EnemyBoss(const sf::Vector2f& startPos)
    : Enemies(1000.f, 200.f, 20.f, startPos), animationRight("assets/Boss/WormRight", "WormRight", 9, 0.1f), //Loading boss texture files
    animationLeft("assets/Boss/WormLeft", "WormLeft", 9, 0.1f),
    currentDirection("right")
{

    setDamage(damage);
    setHP(hp);
    setSpeed(speed);
    setPosition(position);

    animationRight.setPosition(position.x, position.y);
    animationLeft.setPosition(position.x, position.y);

    animationRight.setScale(4.f, 4.f);
    animationLeft.setScale(4.f, 4.f);


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

    updateKnockFlash(dt.asSeconds());
}

void EnemyBoss::takeDamage(float dmg) {
    if (attackCooldown.getElapsedTime().asSeconds() >= attackCooldownTime) {
        hp -= dmg;
        attackCooldown.restart();
    }
}
void EnemyBoss::setDamage(float dmg){
    this->damage=dmg;
}
float EnemyBoss::getDamage() const{
    return this->damage;
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


void EnemyBoss::setHP(float hp_) {
    hp = hp_;
}

float EnemyBoss::getSpeed() const{
    return speed;
}
void EnemyBoss::setSpeed(float spd) {
    this->speed = spd;
}

void EnemyBoss::setPosition(sf::Vector2f pos){
    position=pos;
    animationLeft.setPosition(pos.x, pos.y);
    animationRight.setPosition(pos.x, pos.y);
}
void EnemyBoss::setColor(const sf::Color &color){
    animationLeft.setColor(color);
    animationRight.setColor(color);

}
void EnemyBoss::applyKnockback(const sf::Vector2f& direction, float strength) {

}

// flash on hit
void EnemyBoss::flashHit(float duration) {
    isFlashActive = true;
    FlashTimer = duration;
    setColor(sf::Color(0, 150, 50));
}


void EnemyBoss::updateKnockFlash(float dt) {
    if (knockTimer > 0.f) {
        setPosition(getPosition()+knockbackVelocity*dt);
        knockTimer -= dt;
    }

    if (isFlashActive) {
        FlashTimer-=dt;
        if (FlashTimer<=0.f) {
            isFlashActive=false;
            setColor(originalColor);
        }
    }
}


