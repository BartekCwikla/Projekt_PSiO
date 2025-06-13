#include "enemy_bat.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Enemy_Bat::Enemy_Bat(sf::Vector2f startPos)
    : Enemies(30.f, 50.f, 5.f, startPos), constY(startPos.y),
     amplitude(60.f), frequency(6.f), timePassed(0.f),
    animation("./assets/Bat", "Bat", 4, 0.14f, 1), facingRight(true)
{
    setDamage(damage);
    setHP(hp);
    setSpeed(speed);
    setPosition(position);

    animation.setScale(1.f, 1.f);
    animation.setPosition(position.x, position.y);
}

void Enemy_Bat::render(sf::RenderWindow& window) {
    animation.draw(window);
}

void Enemy_Bat::update(sf::Time& time, const sf::Vector2f&) {
    float dt = time.asSeconds();
    timePassed += dt;
    //X asix is constans
    //Y asix osscilation - sine wave function
    position.y = constY + amplitude * std::sin(frequency * timePassed);

    animation.setPosition(position.x, position.y);
    animation.update(dt);

    updateKnockFlash(dt);
}

//Damage
void Enemy_Bat::takeDamage(float dmg) {
    hp -= dmg;
}
void Enemy_Bat::setDamage(float dmg){
    this->damage = dmg;
}

float Enemy_Bat::getDamage() const{
    return this->damage;
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

void Enemy_Bat::setHP(float hp_) {
    hp = hp_;
}


float Enemy_Bat::getSpeed() const{
    return speed;
}
void Enemy_Bat::setSpeed(float spd) {
    this->speed = spd;
}
void Enemy_Bat::setPosition(sf::Vector2f pos){
    position=pos;
    animation.setPosition(pos.x, pos.y);
}



void Enemy_Bat::setColor(const sf::Color &color){
    animation.setColor(color);

}

void Enemy_Bat::applyKnockback(const sf::Vector2f& direction, float strength) {
    knockbackVelocity = direction * strength;
    knockTimer = 0.1f;
}

// flash on hit
void Enemy_Bat::flashHit(float duration){
    isFlashActive = true;
    FlashTimer = duration;
    setColor(sf::Color::Red);
}


void Enemy_Bat::updateKnockFlash(float dt) {
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



