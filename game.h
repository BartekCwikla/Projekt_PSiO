#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "player.h"
#include "enemies.h"
#include "weapon.h"
#include "projectile.h"
#include "hud.h"
#include "map.h"

// Main class
class Game
{
private:
    sf::RenderWindow window;
    sf::View view;
    sf::Clock enemyspawnClock;
    Player player;
    std::vector<std::unique_ptr<Enemies>> enemies;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    HUD hud;
    Map map;
    int waveNumber;


public:
    Game();
    void run();
    void handleEvents();
    void update(sf::Time& dt);
    void render();
    void spawnEnemies();
    void updateWave();
    sf::Vector2f generateSpawnPositionNear(const sf::Vector2f& playerPos, const sf::FloatRect& mapBounds, float minDist, float maxDist);



};

#endif // GAME_H
