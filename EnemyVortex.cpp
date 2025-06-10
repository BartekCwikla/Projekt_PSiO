#include "enemyvortex.h"
#include "animation.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

EnemyVortex::EnemyVortex(const sf::Vector2f& startPos)
    : Enemies(50.f, 80.f, 0.f, startPos), angle(0.f), angleSpeed(180.f),
    vortex("assets/Vortex", "vortex", 4, 0.1f), phaseDifference(rand()%360)
{
    setDamage(damage); //0 Damage
    setHP(hp);
    setSpeed(speed);
    setPosition(position);

    vortex.setPosition(position.x, position.y);
    vortex.setScale(5.f, 5.f);
}

void EnemyVortex::update(sf::Time& dt, const sf::Vector2f& playerPos) {
    float time = dt.asSeconds();

    // Spinning motion logic
    angle +=angleSpeed*time;
    velocity.x=std::cos(angle*0.0174f+phaseDifference)*speed; //0,0174 is equals 3,141592/180 in radians
    velocity.y=std::sin(angle*0.0174f+phaseDifference)*speed; //Vortex is moving around the circle and its getting more speed in time
    sf::Vector2f repulsion=(playerPos - position)*1.0f;
    position +=(velocity+repulsion)* time;

    vortex.setPosition(position.x, position.y);
    vortex.update(time);
    updateKnockFlash(dt.asSeconds());
}

sf::Vector2f EnemyVortex::recoilForce(const sf::Vector2f& playerPos) const{
    sf::Vector2f direction = playerPos - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);//Radius to the player

    if(distance==0.f)
        return {0.f,0.f};

    direction/= distance;
    float maxRange=300.f; // The repulsion force works only, when player is in close distance to the vortex

    if (distance < maxRange){
        float strength =(maxRange - distance)/maxRange*500.f; //Dynamiclly increase the force of repulsion, when player getting closer to the vortex
        return direction*strength;
    }

    return {0.f, 0.f}; //Nothing happens when player is far away the vortex
}


void EnemyVortex::render(sf::RenderWindow& window) {
    vortex.draw(window);
}

void EnemyVortex::takeDamage(float dmg) {
    hp -= dmg;
}
void EnemyVortex::setDamage(float dmg){
    this->damage=dmg;
}

float EnemyVortex::getDamage() const{
    return this->damage;
}

sf::FloatRect EnemyVortex::getBounds() const {
    return vortex.getGlobalBounds();
}

sf::Vector2f EnemyVortex::getPosition() const {
    return position;
}

float EnemyVortex::getHP() const {
    return hp;
}

void EnemyVortex::setPosition(sf::Vector2f pos){
    position=pos;
    vortex.setPosition(pos.x, pos.y);
}

void EnemyVortex::setHP(float hp_) {
    hp = hp_;
}
float EnemyVortex::getSpeed() const{
    return speed;
}
void EnemyVortex::setSpeed(float spd) {
    this->speed = spd;
}
void EnemyVortex::setColor(const sf::Color &color){
   vortex.setColor(color);

}

void EnemyVortex::applyKnockback(const sf::Vector2f& direction, float strength) {
    knockbackVelocity = direction * strength;
    knockTimer = 0.1f;
}

void EnemyVortex::flashHit(float duration) {
    isFlashActive = true;
    FlashTimer = duration;
    setColor(sf::Color::White);
}

void EnemyVortex::updateKnockFlash(float dt) {
    if (knockTimer > 0.f) {
        setPosition(getPosition() + knockbackVelocity * dt);
        knockTimer -= dt;
    }

    if (isFlashActive) {
        FlashTimer -= dt;
        if (FlashTimer <= 0.f) {
            isFlashActive = false;
            setColor(originalColor);
        }
    }
}
