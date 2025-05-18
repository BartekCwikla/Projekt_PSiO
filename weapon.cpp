#include "weapon.h"
#include "projectile.h"


Weapon::Weapon()
    : name("Unknown")
    , level(0)
    , damage(0.f)
{ }


std::unique_ptr<Projectile>
Weapon::fire(sf::Vector2f, sf::Vector2f)
{

    return nullptr;
}




