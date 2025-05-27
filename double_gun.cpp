#include "double_gun.h"
#include "bullet.h"



std::vector<std::unique_ptr<Projectile>> DoubleGun::fire(sf::Vector2f position, sf::Vector2f direction) {
    std::vector<std::unique_ptr<Projectile>> shots;
    // This line creates a reversed direction for the second bullet
    sf::Vector2f reversed(-direction.x, -direction.y);
    shots.emplace_back(std::make_unique<Bullet>(direction, position, getVelocity(), getRange(), getDamage()));
    shots.emplace_back(std::make_unique<Bullet>(reversed, position, getVelocity(), getRange(), getDamage()));
    return shots;
}
