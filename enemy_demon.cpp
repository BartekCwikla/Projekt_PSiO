#include "enemy_demon.h"
#include <cmath>

Enemy_Demon::Enemy_Demon(const sf::Vector2f& startPos)
    : Enemies(10.f, 80.f, 4.f, startPos),
    animLeft("./assets/Demon/DemonLeft", "DemonLeft", 8, 0.14f, 1),
    animRight("./assets/Demon/DemonRight", "DemonRight", 8, 0.14f, 1),
    facingLeft(true)
{

    setDamage(damage);
    setHP(hp);
    setSpeed(speed);
    setPosition(position);

    animLeft.setScale(1.f, 1.f);
    animRight.setScale(1.f, 1.f);
    animLeft.setPosition(position.x, position.y);
    animRight.setPosition(position.x, position.y);
}

void Enemy_Demon::render(sf::RenderWindow& window){
    if(facingLeft)
        animLeft.draw(window);
    else
        animRight.draw(window);
}

void Enemy_Demon::update(sf::Time& dt, const sf::Vector2f& playerPos){
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

void Enemy_Demon::takeDamage(float dmg){
    hp -= dmg;
}

void Enemy_Demon::setDamage(float dmg){
    this->damage = dmg;
}

float Enemy_Demon::getDamage() const{
    return this->damage;
}

sf::FloatRect Enemy_Demon::getBounds() const{
    return facingLeft ? animLeft.getGlobalBounds() : animRight.getGlobalBounds();
}

sf::Vector2f Enemy_Demon::getPosition() const{
    return position;
}

float Enemy_Demon::getHP() const{
    return hp;
}

void Enemy_Demon::setHP(float hp_){
    hp = hp_;
}

float Enemy_Demon::getSpeed() const{
    return speed;
}

void Enemy_Demon::setSpeed(float spd){
    this->speed = spd;
}

void Enemy_Demon::setPosition(sf::Vector2f pos){
    position = pos;
    animLeft.setPosition(pos.x, pos.y);
    animRight.setPosition(pos.x, pos.y);
}

void Enemy_Demon::setColor(const sf::Color &color){
    animLeft.setColor(color);
    animRight.setColor(color);

}
void Enemy_Demon::applyKnockback(const sf::Vector2f& direction, float strength) {
    knockbackVelocity = direction * strength;
    knockTimer = 0.1f;
}

// flash on hit
void Enemy_Demon::flashHit(float duration) {
    isFlashActive = true;
    FlashTimer = duration;
    setColor(sf::Color::Red);
}


void Enemy_Demon::updateKnockFlash(float dt) {
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



