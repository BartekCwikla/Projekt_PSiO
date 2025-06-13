#include "enemyknight.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

EnemyKnight::EnemyKnight(const sf::Vector2f& startPos)
    : Enemies(50.f, 100.f, 15.f, startPos),
    animLeft("./assets/Knight/KnightLeft", "KnightLeft", 8, 0.14f, 1),
    animRight("./assets/Knight/KnightRight", "KnightRight", 8, 0.14f, 1),
    facingLeft(true)
{
    setDamage(damage);
    setHP(hp);
    setSpeed(speed);
    setPosition(position);

    animLeft.setScale(2.f, 2.f);
    animRight.setScale(2.f, 2.f);
    animLeft.setPosition(position.x, position.y);
    animRight.setPosition(position.x, position.y);
}

void EnemyKnight::render(sf::RenderWindow& window){
    if(facingLeft)
        animLeft.draw(window);
    else
        animRight.draw(window);
}

void EnemyKnight::update(sf::Time& dt, const sf::Vector2f& playerPos){
    float delta = dt.asSeconds();

    sf::Vector2f dir=playerPos-position;
    float len = std::sqrt(dir.x*dir.x+ dir.y* dir.y);
    if(len != 0)
        dir /=len;

    position +=dir *speed*delta;
    facingLeft=dir.x < 0;

    if(facingLeft){
        animLeft.setPosition(position.x, position.y);
        animLeft.update(delta);
    }else{
        animRight.setPosition(position.x, position.y);
        animRight.update(delta);
    }

    updateKnockFlash(dt.asSeconds());
}

void EnemyKnight::takeDamage(float dmg){
    hp -= dmg;
}

void EnemyKnight::setDamage(float dmg){
    this->damage = dmg;
}

float EnemyKnight::getDamage() const{
    return this->damage;
}

sf::FloatRect EnemyKnight::getBounds() const{
    return facingLeft ? animLeft.getGlobalBounds() : animRight.getGlobalBounds();
}

sf::Vector2f EnemyKnight::getPosition() const{
    return position;
}

float EnemyKnight::getHP() const{
    return hp;
}

void EnemyKnight::setHP(float hp_){
    hp = hp_;
}

float EnemyKnight::getSpeed() const{
    return speed;
}

void EnemyKnight::setSpeed(float spd){
    this->speed = spd;
}

void EnemyKnight::setPosition(sf::Vector2f pos){
    position = pos;
    animLeft.setPosition(pos.x, pos.y);
    animRight.setPosition(pos.x, pos.y);
}

void EnemyKnight::setColor(const sf::Color &color){
    animLeft.setColor(color);
    animRight.setColor(color);
}

void EnemyKnight::applyKnockback(const sf::Vector2f& direction, float strength) {
    knockbackVelocity = direction * strength;
    knockTimer = 0.1f;
}

// flash on hit
void EnemyKnight::flashHit(float duration) {
    isFlashActive = true;
    FlashTimer = duration;
    setColor(sf::Color::Red);
}


void EnemyKnight::updateKnockFlash(float dt) {
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



