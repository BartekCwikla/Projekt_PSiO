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
    sf::Text waveText, timerText;

    sf::Clock waveClock;
    int currentWave;

public:
    HUD();
    float getWavesInformationPosition() const;
    void update(const Player& player, const sf::RenderWindow& window, int currentWave, float waveTime);
    void draw(sf::RenderWindow& window);
    const sf::Font& getFont() const;
};

#endif //HUD_H
