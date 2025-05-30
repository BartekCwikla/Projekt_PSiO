#include "enemyvortex.h"
#include "animation.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

EnemyVortex::EnemyVortex(const sf::Vector2f& startPos)
    : position(startPos), angle(0.f), angleSpeed(180.f),
    vortex("assets/Vortex", "vortex", 4, 0.1f), phaseDifference(rand()%360)
{
    hp = 25.f;
    speed = 80.f;
    damage = 0.f;
    setDamage(damage); //Only force. Vortex does not taking any damage

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

sf::FloatRect EnemyVortex::getBounds() const {
    return vortex.getGlobalBounds();
}

sf::Vector2f EnemyVortex::getPosition() const {
    return position;
}

float EnemyVortex::getHP() const {
    return hp;
}


void EnemyVortex::setHP(float& hp_) {
    hp_ = hp;
}
