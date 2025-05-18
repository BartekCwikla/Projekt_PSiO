#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
//#include "enemies.h"
//#include "projectiles.h"

class Weapons;
class Projectiles;
class Enemies;

class Player
{
private:
    float hp=0.f;
    int lvl=0, cash=0;
    std::vector<std::unique_ptr<Weapons>> weapons;
    sf::Clock attackClock;
    sf::RectangleShape body; // temporarily, later sf::Sprite
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

public:
    Player();
    ~Player();
    void attack(std::vector<std::unique_ptr<Projectiles>>& projectiles);
    void update(sf::Time dt);
    void move(const sf::Vector2f& dir);
    void takeDamage(const int& dam);
    void castSpecial(); //optional
    void setPosition(const sf::Vector2f& pos);
    const sf::RectangleShape& getBody() const;
    const sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

    // This specifies a direction, that player should move in. There are eigth general directions, that can be achieved,
    // by pressing different combinations of 'WSAD'
    const sf::Vector2f getDirection() const;
    void setDirection(sf::Vector2f);
    void setDirectionY(float);
    void setDirectionX(float);
    float getSpeed() const;
    void getSpeed(float);
};

#endif // PLAYER_H
