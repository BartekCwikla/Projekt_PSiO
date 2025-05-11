#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics.hpp>
//#include "player.h"
class Player;

class HUD
{
private:
    sf::RectangleShape hpBar, expBar;
    sf::Text infoText;
public:
    HUD();
    void update(const Player&);
    void draw(sf::RenderWindow& window);
};

#endif // HUD_H
