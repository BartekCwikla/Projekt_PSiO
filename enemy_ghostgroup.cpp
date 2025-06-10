#include "enemy_ghostgroup.h"
#include <cmath>

Enemy_GhostGroup::Enemy_GhostGroup(const sf::Vector2f& startPos, const sf::Vector2f& dir)
    : Enemies(4.f, 700.f, 2.f, startPos), direction(dir), constY(startPos.y), amplitude(20.f),
    frequency(2.f), timePassed(0.f),
    animationLeft("./assets/Ghost/GhostLeft", "GhostLeft", 12, 0.14f, 1),
    animationRight("./assets/Ghost/GhostRight", "GhostRight", 12, 0.14f, 1),
    facingLeft(true)
{

    setDamage(damage);
    setHP(hp);
    setSpeed(speed);
    setPosition(position);

    animationLeft.setScale(0.4f, 0.4f);
    animationRight.setScale(0.4f, 0.4f);
    animationLeft.setPosition(startPos.x, position.y);
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

void Enemy_GhostGroup::setPosition(sf::Vector2f pos){
    position=pos;
    animationLeft.setPosition(pos.x, pos.y);
    animationRight.setPosition(pos.x, pos.y);
}

void Enemy_GhostGroup::setColor(const sf::Color &color){
    animationLeft.setColor(color);
    animationRight.setColor(color);
}

 void Enemy_GhostGroup::applyKnockback(const sf::Vector2f& direction, float strength) {
    knockbackVelocity = direction * strength;
    knockTimer = 0.1f;
}

// flash on hit
void Enemy_GhostGroup::flashHit(float duration) {
    isFlashActive = true;
    FlashTimer = duration;
    setColor(sf::Color::Blue);
}


void Enemy_GhostGroup::updateKnockFlash(float dt) {
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



