#ifndef WEAPON_H
#define WEAPON_H
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Player;
class Enemies;
class Projectile;

class Weapon
{
protected:
    std::string name="Unknown";
    int level=0;
    float damage=0.f;
    sf::Clock coolDown;
public:
    Weapon();
    virtual ~Weapon()=default;
    virtual void upgrade()=0;
    virtual std::unique_ptr<Projectile> fire(sf::Vector2f, sf::Vector2f);

    void setDamage(float new_damage);
    float getDamage() const;

};







#endif // WEAPON_H
