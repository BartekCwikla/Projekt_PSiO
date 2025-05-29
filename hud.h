#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics.hpp>

class Player;

class HUD {
private:
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarFront;

    sf::RectangleShape expBarBack;
    sf::RectangleShape expBarFront;

    sf::Font font;
    sf::Text hpText, expText, lvlText;

public:
    HUD();
    void update(const Player& player, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    const sf::Font& getFont() const;
};

#endif //HUD_H
