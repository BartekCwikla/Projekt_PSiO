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

public:
    Player();
    ~Player();
    void attack(std::vector<std::unique_ptr<Projectiles>>& projectiles);
    void update(sf::Time dt);
    void move(const sf::Vector2f& dir);
    void takeDamage(const int& dam);
    void castSpecial(); //optional
};

#endif // PLAYER_H
