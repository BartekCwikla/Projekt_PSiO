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
    sf::Texture texture;

public:
    Weapon();
    virtual ~Weapon()=default;
    virtual void upgrade()=0;
    virtual std::vector<std::unique_ptr<Projectile>> fire(sf::Vector2f, sf::Vector2f) = 0;

    void setDamage(float new_damage);
    float getDamage() const;

    std::string getName() const;
    void setName(const std::string &newName);
    const sf::Texture& getTexture() const;
};

#endif // WEAPON_H
