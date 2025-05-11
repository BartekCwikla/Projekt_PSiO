#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "player.h"
#include "enemies.h"
#include "weapons.h"
#include "projectiles.h"
#include "hud.h"

// Main class
class Game
{
private:
    sf::RenderWindow window;

    sf::View view; //optional

    Player player;
    std::vector<std::unique_ptr<Enemies>> enemies;
    std::vector<std::unique_ptr<Projectiles>> projectiles;
    HUD hud;
    int waveNumber;


public:
    Game();
    void run();
    void handleEvents();
    void update(sf::Time& dt);
    void render();
    void spawnEnemies();
    void updateWave();

};

#endif // GAME_H
