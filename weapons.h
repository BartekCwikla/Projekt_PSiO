#ifndef WEAPONS_H
#define WEAPONS_H
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Player;
class Enemies;

class Weapons
{
protected:
    std::string name="Unknown";
    int level=0;
    float damage=0.f;
    sf::Clock coolDown;
public:
    Weapons();
    virtual ~Weapons()=default;
   virtual void attack(Player&, std::vector<std::unique_ptr<Enemies>>&)=0;
    virtual void upgrade()=0;

};

#endif // WEAPONS_H
