#include "player.h"
#include "weapon.h"
#include "projectile.h"
#include "gun.h"

Player::Player() : body(sf::Vector2f(100, 100)), position(sf::Vector2f(1200, 750)), speed(500.0) {

    auto g = std::make_unique<Gun>();


    current_weapon = g.get();
    weapons.push_back(std::move(g));

    direction = {0,0};
    last_direction = {1,0};
}


Player::~Player() = default;

const sf::RectangleShape& Player::getBody() const {
    return body;
}

sf::FloatRect Player::getGlobalBounds() const {
    return body.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const {
    return body.getPosition();
}
void Player::setPosition(const sf::Vector2f& pos){
    body.setPosition(pos);
}


// Moving player in a direction specified by 'dir' argument of sf::Vector2f type
void Player::move(const sf::Vector2f& dir) {
    body.move(dir);
}


const sf::Vector2f Player::getDirection() const {
    return direction;
}

void Player::setDirection(sf::Vector2f dir) {
    direction = dir;
}

void Player::setDirectionX(float x) {
    direction.x = x;
}

void Player::setDirectionY(float y) {
    direction.y = y;
}

void Player::setLastDirection(sf::Vector2f dir) {
    last_direction = dir;
}


float Player::getSpeed() const {
    return speed;
}


std::unique_ptr<Projectile> Player::fire() {
    return current_weapon->fire(getPosition(), last_direction);
}


Weapon* Player::getCurrentWeapon() {
    return current_weapon;
}


