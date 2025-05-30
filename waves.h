#ifndef WAVES_H
#define WAVES_H
#include <SFML/Graphics.hpp>
class Waves
{
    sf::Clock gameClock;
    sf::Clock waveClock;
    int currentWave = 1;
    float waveTime = 60.f; // seconds
    bool waveActive = true;
    int enemiesToSpawn = 30;
    float enemyHP = 20.f;
    float enemyDamage = 5.f;
    sf::Font font;
    sf::Text waveText;
    sf::Text timerText;

public:
    Waves();

    void update(const sf::RenderWindow& window) ;

    void draw(sf::RenderWindow& window);
    bool isNewWaveReady() const;
    void nextWave();
    int getEnemiesToSpawn() const;
    float getEnemyHP() const;
    float getEnemyDamage() const;
    int getCurrentWave() const;
};

#endif // WAVES_H
