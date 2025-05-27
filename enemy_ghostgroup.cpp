#include "enemy_ghostgroup.h"
#include <cmath>

Enemy_GhostGroup::Enemy_GhostGroup(const sf::Vector2f& startPos, const sf::Vector2f& dir)
    :  direction(dir), constY(startPos.y), speed(1000.f), hp(5.f), amplitude(20.f), frequency(2.f), timePassed(0.f)
{
    setDamage(2.f);
    body.setSize(sf::Vector2f(20.f, 20.f));
    body.setFillColor(sf::Color::Blue);
    body.setOrigin(10.f, 10.f);
    body.setPosition(startPos);
}

void Enemy_GhostGroup::update(sf::Time& dt, const sf::Vector2f&) {
    float delta = dt.asSeconds();
    timePassed += delta;

    // X asix direct move
    float dx = direction.x * speed * delta;

    // Y asix little osscilation - sine wave function
    float dy = amplitude * std::sin(frequency * timePassed);

    body.move(dx, 0.f);
    body.setPosition(body.getPosition().x, constY + dy);
}


void Enemy_GhostGroup::render(sf::RenderWindow& window)
{
    window.draw(body);
}

void Enemy_GhostGroup::takeDamage(float dmg)
{
    hp -= dmg;
}

//Getters
sf::FloatRect Enemy_GhostGroup::getBounds() const
{
    return body.getGlobalBounds();
}

sf::Vector2f Enemy_GhostGroup::getPosition() const
{
    return body.getPosition();
}

float Enemy_GhostGroup::getHP() const
{
    return hp;
}
