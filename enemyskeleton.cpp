#include "enemyskeleton.h"
#include "cmath"
EnemySkeleton::EnemySkeleton(const sf::Vector2f& startPos)
    : Enemies(80.f, 80.f, 10.f, startPos),
    animationLeft("assets/Skeleton/SkeletonLeft", "SkeletonLeft", 12, 0.12f, 1),
    animationRight("assets/Skeleton/SkeletonRight", "SkeletonRight", 12, 0.12f, 1),
    facingRight(true)
{
    setDamage(damage);
    setHP(hp);
    setSpeed(speed);
    setPosition(position);

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

    updateKnockFlash(dt.asSeconds());
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

void EnemySkeleton::setPosition(sf::Vector2f pos){
    position=pos;
    animationLeft.setPosition(pos.x, pos.y);
    animationRight.setPosition(pos.x, pos.y);
}

void EnemySkeleton::setColor(const sf::Color &color){
    animationLeft.setColor(color);
    animationRight.setColor(color);

}
void EnemySkeleton::applyKnockback(const sf::Vector2f& direction, float strength) {
    knockbackVelocity = direction * strength;
    knockTimer = 0.1f;
}

// flash on hit
void EnemySkeleton::flashHit(float duration){
    isFlashActive = true;
    FlashTimer = duration;
    setColor(sf::Color::Red);
}


void EnemySkeleton::updateKnockFlash(float dt){
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

