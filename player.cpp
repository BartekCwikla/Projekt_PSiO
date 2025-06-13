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
#include "meteor_rain.h"
#include "fireball.h"




sf::Vector2f Player::getLastDirection() const
{
    return last_direction;
}

Player::Player()
    : body(sf::Vector2f(70, 70)),
    speed(300.f), hp(100.f), maxHp(100.f), exp(0.f), ExpNextLvl(100.f),
    N("./assets/PlayerCharacter/N", "N", 14, 0.08f,1),
    S("./assets/PlayerCharacter/S", "S", 14, 0.08f,1),
    W("./assets/PlayerCharacter/W", "W", 14, 0.08f,1),
    E("./assets/PlayerCharacter/E", "E", 14, 0.08f,1),
    NE("./assets/PlayerCharacter/NE", "NE", 14, 0.08f,1),
    NW("./assets/PlayerCharacter/NW", "NW", 14, 0.08f,1),
    SE("./assets/PlayerCharacter/SE", "SE", 14, 0.08f,1),
    SW("./assets/PlayerCharacter/SW", "SW", 14, 0.08f,1),
    isalive(true),
    shooting_direction(sf::Vector2f(1,1))

    {
    auto g = std::make_unique<DoubleGun>();
    auto g1 = std::make_unique<Gun>();
    auto g2 = std::make_unique<ExplodingGun>();
    auto g3 = std::make_unique<PiercingGun>();
    auto g4 = std::make_unique<Axe>();
    auto g5 = std::make_unique<QuadGun>();
    auto g6 = std::make_unique<Boomerang>();

    body.setPosition(sf::Vector2f(1200, 750));

    current_weapon = g1.get();
    weapons.push_back(std::move(g1));
    available_weapons.push_back(std::move(g));
    available_weapons.push_back(std::move(g1));
    available_weapons.push_back(std::move(g2));
    available_weapons.push_back(std::move(g3));
    available_weapons.push_back(std::move(g4));
    available_weapons.push_back(std::move(g5));
    available_weapons.push_back(std::move(g6));

    N.setScale(2.f,2.f);
    S.setScale(2.f, 2.f);
    E.setScale(2.f,2.f);
    S.setScale(2.f,2.f);
    SE.setScale(2.f,2.f);
    SW.setScale(2.f,2.f);
    NW.setScale(2.f,2.f);
    NE.setScale(2.f,2.f);
    W.setScale(2.f,2.f);

    auto spwr1 = std::make_unique<MeteorRain>(3.f, 100.f, 15);
    auto spwr2 = std::make_unique<Fireball>(1000.f, 400.f);

    super_powers.push_back(std::move(spwr1));
    super_powers.push_back(std::move(spwr2));

    direction = {0,0};
    last_direction = {1,0};
}


Player::~Player() = default;


void Player::update(sf::Time dt){
    playerAnimation(dt.asSeconds());
}

void Player::playerAnimation(float dt){
    if (direction == sf::Vector2f(0.f, 0.f)) {
        if (currentAnimation)
            currentAnimation->setFrame(0);
        return;
    }


    last_direction = direction;


    if (direction.x == 0.f && direction.y < 0.f) currentAnimation = &N;
    else if (direction.x > 0.f && direction.y < 0.f) currentAnimation = &NE;
    else if (direction.x > 0.f && direction.y == 0.f) currentAnimation = &E;
    else if (direction.x > 0.f && direction.y > 0.f) currentAnimation = &SE;
    else if (direction.x == 0.f && direction.y > 0.f) currentAnimation = &S;
    else if (direction.x < 0.f && direction.y > 0.f) currentAnimation = &SW;
    else if (direction.x < 0.f && direction.y == 0.f) currentAnimation = &W;
    else if (direction.x < 0.f && direction.y < 0.f) currentAnimation = &NW;
    else if (direction.x == 0.f && direction.y == 0.f) currentAnimation = &NW;

    if (currentAnimation) {
        currentAnimation->setPosition(getPosition().x, getPosition().y);
        currentAnimation->update(dt);
    }
}

void Player::draw(sf::RenderWindow &window){
    if (currentAnimation) {
        currentAnimation->draw(window);
    }
}

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

void Player::keyboardMovement(){
    sf::Vector2f input(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) input.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) input.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) input.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) input.x += 1.f;
    setDirection(input);
}


// This function determines shooting direction and replaces the old approach using movement direction for shooting.
// It takes delta time as a parameter to wait for a second possible input not to shoot immediately after one key is pressed,
// as direction can be defined after pressing two.
void Player::determineShootingDirection(sf::Time dt) {
    sf::Vector2f currentInput(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) currentInput.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) currentInput.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) currentInput.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) currentInput.x += 1.f;

    if (currentInput != sf::Vector2f(0.f, 0.f)) {
        if (!shootInputActive) {
            shootInputActive = true;
            pendingShootDirection = currentInput;
            shootDelayTimer.restart();
        } else {
            // Update pending direction with new input
            pendingShootDirection = currentInput;
        }
    } else {
        // if no keys pressed, reset
        shootInputActive = false;
    }

    // Set shooting direction if buffer time elapsed
    if (shootInputActive && shootDelayTimer.getElapsedTime().asSeconds() >= inputBufferTime) {
        setShootingDirection(pendingShootDirection);
        shootInputActive = false; // Reset for next input
    } else {
        // Don't shoot during buffer time
        setShootingDirection(sf::Vector2f(0.f, 0.f));
    }
}


float Player::getSpeed() const {
    return speed;
}


std::vector<std::unique_ptr<Projectile>> Player::fire() {
    return current_weapon->fire(getPosition(), shooting_direction);
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
        else if(lvl++){
            hp += 20.f;
            if(hp >= maxHp)
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

// Add weapon for a player and make it active immediately
void Player::addWeapon(std::unique_ptr<Weapon> w) {
    weapons.push_back(std::move(w));
    current_weapon = weapons.back().get();
}

void Player::addSuperPower(std::unique_ptr<SuperPower> sp) {
    super_powers.push_back(std::move(sp));
}

void Player::selectWeapon(std::size_t index) {
    if (index < weapons.size()) {
        current_weapon = weapons[index].get();
    }
}


bool Player::isAlive(){
    if(hp > 0 && hp <= maxHp)
        isalive = true;
    else if(hp<=0)
        isalive = false;
}

void Player::GameOverStopMove(){
    this->direction = sf::Vector2f{0.f,0.f};
}


sf::Vector2f Player::getShootingDirection() const
{
    return shooting_direction;
}

void Player::setShootingDirection(const sf::Vector2f &newShootingDirection)
{
    shooting_direction = newShootingDirection;
}



