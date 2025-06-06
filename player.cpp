#include "player.h"
#include "weapon.h"
#include "projectile.h"
#include "gun.h"
#include "double_gun.h"
#include "exploding_gun.h"
#include "piercing_gun.h"
#include "quad_gun.h"
#include "axe.h"
#include "boomerang.h"
#include <iostream>
#include "meteor_rain.h"


Player::Player()
    : body(sf::Vector2f(100, 100)), position(sf::Vector2f(1200, 750)),
    speed(300.f), hp(100.f), maxHp(100.f), exp(0.f), ExpNextLvl(100.f)
{
    auto g = std::make_unique<DoubleGun>();
    auto g1 = std::make_unique<Gun>();
    auto g2 = std::make_unique<ExplodingGun>();
    auto g3 = std::make_unique<PiercingGun>();
    auto g4 = std::make_unique<Axe>();
    auto g5 = std::make_unique<QuadGun>();
    auto g6 = std::make_unique<Boomerang>();

    current_weapon = g.get();
    weapons.push_back(std::move(g));
    weapons.push_back(std::move(g1));
    weapons.push_back(std::move(g2));
    weapons.push_back(std::move(g3));
    weapons.push_back(std::move(g4));
    weapons.push_back(std::move(g5));
    weapons.push_back(std::move(g6));

    auto spwr1 = std::make_unique<MeteorRain>(3.f, 100.f, 15);

    super_powers.push_back(std::move(spwr1));

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


std::vector<std::unique_ptr<Projectile>> Player::fire() {
    return current_weapon->fire(getPosition(), last_direction);
}

float Player::getHP() const {
    return hp;
}

float Player::getMaxHP() const {
    return maxHp;
}

float Player::getExp() const {
    return exp;
}

float Player::getExpNextLvl() const {
    return ExpNextLvl;
}

const std::vector<std::unique_ptr<SuperPower>>& Player::getSuperPowers() const
{
    return super_powers;
}

int Player::getLvl() const {
    return lvl;
}

int Player::getMaxLvl() const {
    return maxLvl;
}
void Player::takeDamage(const int& dam) {
    hp -= dam;
    if(hp <= 0.f)
        hp=0.f;
}

//Future method that adding experience and loading the exp bar
void Player::addMaxLevelTreshold(float amount) {
    exp += amount;
    float increasedHp = 20.f;

    while (exp >= ExpNextLvl) {
        exp -= ExpNextLvl;
        lvl++;
        ExpNextLvl *= 1.3f; // The threshold to reach the next level is rising

        if(lvl%10 == 0){ //When player reach levels: 10,20,30,40,50, his HP will increased;
            maxHp+=increasedHp;
            hp=maxHp;
        }

    }
}

Weapon* Player::getCurrentWeapon() {
    return current_weapon;
}

const std::vector<std::unique_ptr<Weapon>>& Player::getWeapons() const {
    return weapons;
}

void Player::selectWeapon(std::size_t index) {
    if (index < weapons.size()) {
        current_weapon = weapons[index].get();
    }
}

