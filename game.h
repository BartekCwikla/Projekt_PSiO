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
#include "exporb.h"

// Main class
class Game
{
private:
    sf::RenderWindow window;
    sf::View view;
    sf::View defaultView; //HUD render
    sf::Clock enemyspawnClock;
    sf::Clock ghostSpawnClock; //New clock to spawns group of ghosts
    float ghostsDelay;
    Player player;
    std::vector<std::unique_ptr<Enemies>> enemies;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    std::vector<std::unique_ptr<ExpOrb>> expOrbs;
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
    void handleShot(std::vector<std::unique_ptr<Projectile>>);
    sf::Vector2f generateSpawnPositionNear(const sf::Vector2f& playerPos, const sf::FloatRect& mapBounds, float minDist, float maxDist);



};

#endif // GAME_H
