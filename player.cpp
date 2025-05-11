#include "player.h"
#include "weapons.h"


Player::Player() : body(sf::Vector2f(100, 100)), position(sf::Vector2f(1200, 750)), speed(500.0) {}


Player::~Player() = default;

const sf::RectangleShape& Player::getBody() const {
    return body;
}

const sf::Vector2f Player::getPosition() const {
    return position;
}


// Moving player in a direction specified by 'dir' argument of sf::Vector2f type
void Player::move(const sf::Vector2f& dir) {
    position += dir;
    body.setPosition(position);
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

float Player::getSpeed() const {
    return speed;
}

