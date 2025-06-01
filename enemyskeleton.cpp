#include "enemyskeleton.h"
#include "cmath"
EnemySkeleton::EnemySkeleton(const sf::Vector2f& startPos)
    : Enemies(80.f, 100.f, 10.f), position(startPos),
    animationLeft("assets/Skeleton/SkeletonLeft", "SkeletonLeft", 12, 0.12f, 1),
    animationRight("assets/Skeleton/SkeletonRight", "SkeletonRight", 12, 0.12f, 1)
{
    setDamage(damage);
    animationLeft.setScale(2.f, 2.f);
    animationRight.setScale(2.f, 2.f);
    animationLeft.setPosition(position.x, position.y);
    animationRight.setPosition(position.x, position.y);
}

void EnemySkeleton::render(sf::RenderWindow& window) {
    if (facingRight)
        animationRight.draw(window);
    else
        animationLeft.draw(window);
}

void EnemySkeleton::update(sf::Time& dt, const sf::Vector2f& playerPos) {
    float delta = dt.asSeconds();

    sf::Vector2f dir = playerPos - position;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0)
        dir /= len;

    position += dir * speed * delta;
    facingRight = (dir.x >= 0);

    if (facingRight) {
        animationRight.setPosition(position.x, position.y);
        animationRight.update(delta);
    } else {
        animationLeft.setPosition(position.x, position.y);
        animationLeft.update(delta);
    }
}

void EnemySkeleton::takeDamage(float dmg) {
    hp -= dmg;
}
void EnemySkeleton::setDamage(float dmg){
    this->damage=dmg;
}

float EnemySkeleton::getDamage() const{
    return this->damage;
}

sf::FloatRect EnemySkeleton::getBounds() const {
    return facingRight ? animationRight.getGlobalBounds() : animationLeft.getGlobalBounds();
}

sf::Vector2f EnemySkeleton::getPosition() const {
    return position;
}

float EnemySkeleton::getHP() const {
    return hp;
}


void EnemySkeleton::setHP(float hp_) {
    hp = hp_;
}
float EnemySkeleton::getSpeed() const{
    return speed;
}
void EnemySkeleton::setSpeed(float spd) {
    this->speed = spd;
}

