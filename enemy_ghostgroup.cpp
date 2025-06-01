#include "enemy_ghostgroup.h"
#include <cmath>

Enemy_GhostGroup::Enemy_GhostGroup(const sf::Vector2f& startPos, const sf::Vector2f& dir)
    : Enemies(4.f, 200.f, 2.f), direction(dir), constY(startPos.y), amplitude(20.f),
    frequency(2.f), timePassed(0.f),
    animationLeft("./assets/Ghost/GhostLeft", "GhostLeft", 12, 0.14f, 1),
    animationRight("./assets/Ghost/GhostRight", "GhostRight", 12, 0.14f, 1),
    facingLeft(true), position(startPos)
{
    setDamage(damage);
    setSpeed(speed);
    setHP(hp);

    animationLeft.setScale(1.f, 1.f);
    animationRight.setScale(1.f, 1.f);
    animationLeft.setPosition(position.x, position.y);
    animationRight.setPosition(position.x, position.y);


}

void Enemy_GhostGroup::render(sf::RenderWindow& window){
    if(facingLeft)
        animationLeft.draw(window);
    else
        animationRight.draw(window);
}

void Enemy_GhostGroup::update(sf::Time& dt, const sf::Vector2f&){
    float delta = dt.asSeconds();
    timePassed += delta;

    float dx = direction.x*speed*delta;

    // Y asix osscilation
    float dy = amplitude*std::sin(frequency *timePassed);

    position.x+=dx;
    position.y=constY+dy;
    facingLeft=(direction.x< 0);

    if(facingLeft){
        animationLeft.setPosition(position.x, position.y);
        animationLeft.update(delta);
    }else{
        animationRight.setPosition(position.x, position.y);
        animationRight.update(delta);
    }
}

void Enemy_GhostGroup::takeDamage(float dmg){
    hp -= dmg;
}
void Enemy_GhostGroup::setDamage(float dmg){
    this->damage = dmg;
}
float Enemy_GhostGroup::getDamage() const{
    return this->damage;
}

sf::FloatRect Enemy_GhostGroup::getBounds() const{
    return facingLeft ? animationLeft.getGlobalBounds() : animationRight.getGlobalBounds();
}

sf::Vector2f Enemy_GhostGroup::getPosition() const{
    return this->position;
}

float Enemy_GhostGroup::getHP() const{
    return this->hp;
}

void Enemy_GhostGroup::setHP(float hp_){
    this->hp = hp_;
}

float Enemy_GhostGroup::getSpeed() const{
    return this->speed;
}

void Enemy_GhostGroup::setSpeed(float spd){
    this->speed = spd;
}
