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
#include "audio.h"
#include "meteor.h"
#include "map.h"
#include "exporb.h"
#include "weapon_factory.h"
#include "superpower_factory.h"


enum class GameState {
    MENU,
    PLAYING,
    EXIT,
    GAMEOVER,
    WIN
};

// Main class
class Game
{
private:
    GameState currentState = GameState::MENU;
    sf::RenderWindow window;
    sf::View view;
    Audio audio;
    sf::View defaultView; //HUD render
    sf::Clock enemyspawnClock;
    sf::Clock ghostSpawnClock; //New clock to spawns group of ghosts
    sf::Clock bossSpawnClock;
    sf::Clock waveClock;
    sf::Clock currentWaveClock;
    sf::Clock FPS;
    bool bossSpawned = false;
    bool testWaveSpawned = false;
    float ghostsDelay;
    int ghostR = 30.f;
    Player player;
    std::vector<std::unique_ptr<Enemies>> enemies;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    std::vector<std::unique_ptr<ExpOrb>> expOrbs;
    std::vector<std::unique_ptr<Meteor>> meteors;
    HUD hud;
    Map map;


    bool gameOver = false;

    int last_level_weapon = 0;
    bool isPaused = false;
    sf::Clock clock;
    std::vector<std::string> availableWeapons;


;
  //  Waves waves;
    int frameCounter;
    int lastWaveNumber = 0;
    int currentWave = 1;
    void wavesLogic();


public:
    Game();
    void run();
    void handleEvents();
    void update(sf::Time& dt);
    void render();
    void spawnEnemies();
    void updateWave();
    void handleShot(std::vector<std::unique_ptr<Projectile>>);
    void spawnEnemyForCurrentWave(int wave);
    sf::Vector2f generateSpawnPositionNear(const sf::Vector2f& playerPos, const sf::FloatRect& mapBounds, float minDist, float maxDist);
    void EnemiesBoundsColision ();
    void FPSlimiter();
    void showMenu();
    GameState getState() const;
    void setState(GameState state);
    bool isWindowOpen() const;
    void GameOver();
    void resetGame();

    void showWeaponChoiceScreen();


};

#endif // GAME_H
