#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
//#include "enemies.h"
//#include "projectile.h"
#include "superpower.h"
#include "animation.h"
#include "weapon_factory.h"

class Weapon;
class Projectile;
class Enemies;

class Player
{
private:
    float hp=100.f, maxHp=100.f;
    int lvl=0, maxLvl=50; //this may be maximum level that player can reach
    float exp=100.f, ExpNextLvl=100.f;
    float speed;
    std::vector<std::unique_ptr<Weapon>> weapons;
    std::vector<std::unique_ptr<Weapon>> available_weapons;
    Weapon* current_weapon = nullptr;
    std::vector<std::unique_ptr<SuperPower>> super_powers;
    sf::Clock attackClock;
    sf::RectangleShape body; // temporarily, later sf::Sprite
    sf::Vector2f position;
    sf::Vector2f direction;
    sf::Vector2f last_direction;
    sf::Vector2f shooting_direction;
    sf::Clock shootDelayTimer;
    bool shootInputActive = false;
    sf::Vector2f pendingShootDirection;
    float inputBufferTime = 0.1f; // 100 ms time to wait for a second input for shooting direction

    Animation N, E, S, W, NE, NW, SE, SW;
    Animation* currentAnimation = nullptr;
    bool isalive;


public:
    Player();
    ~Player();
    void attack(std::vector<std::unique_ptr<Projectile>>& projectiles);
    void update(sf::Time dt);
    void move(const sf::Vector2f& dir);
    void takeDamage(const int& dam);
    void castSpecial(); //optional
    void setPosition(const sf::Vector2f& pos);
    const sf::RectangleShape& getBody() const;
    const sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void playerAnimation(float dt);

    // This specifies a direction, that player should move in. There are eigth general directions, that can be achieved,
    // by pressing different combinations of 'WSAD'
    const sf::Vector2f getDirection() const;
    void setDirection(sf::Vector2f);
    void setDirectionY(float);
    void setDirectionX(float);
    void setLastDirection(sf::Vector2f);
    void keyboardMovement();
    void determineShootingDirection(sf::Time dt);
    void draw(sf::RenderWindow& window);


    //Getter methods for any float or integer variables:
    float getSpeed() const;
    void getSpeed(float);

    float getHP() const;
    float getMaxHP() const;

    int getLvl() const;
    int getMaxLvl() const;

    float getExp() const;
    float getExpNextLvl() const;

    const std::vector<std::unique_ptr<SuperPower>>& getSuperPowers() const;
    void addSuperPower(std::unique_ptr<SuperPower> s);

    //addExp method changes the ExpNextLvl variable after reaching new level
    void addMaxLevelTreshold(float amount);

    Weapon* getCurrentWeapon();


    std::vector<std::unique_ptr<Projectile>> fire();

    const std::vector<std::unique_ptr<Weapon>>& getWeapons() const;
    void addWeapon(std::unique_ptr<Weapon> w);

    void selectWeapon(std::size_t index);


    bool isAlive();
    void GameOverStopMove();

    sf::Vector2f getShootingDirection() const;
    void setShootingDirection(const sf::Vector2f &newShooting_direction);

    friend WeaponFactory;

};

#endif // PLAYER_H
