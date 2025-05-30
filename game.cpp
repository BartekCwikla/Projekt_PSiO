#include "game.h"
#include "enemy_demon.h"
#include "exporb.h"
#include "enemy_bat.h"
#include "enemy_ghostgroup.h"
#include "enemyboss.h"
#include "enemyvortex.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "exploding_projectile.h"

Game::Game() : window(sf::VideoMode(2400, 1500), "Window"),
    view(window.getDefaultView()),ghostsDelay(static_cast<float>(rand()%15) + 30.f),  player()
{
    map.load("./assets/map/ground_stone.png", 256, 64, 64); //Map size is 16 384 x 16 384 pixels
    view.setSize(2400,1500);
    defaultView = window.getDefaultView();

    player.setPosition(map.getSize()/2.f);
    view.setCenter(player.getPosition());

}

void Game::run() {
    sf::Clock clock;

    while(window.isOpen()) {

        sf::Time dt = clock.restart();
        handleEvents();
        update(dt);
        render();
    }
}


void Game::handleShot(std::vector<std::unique_ptr<Projectile>> v) {
    for (auto &p : v ) {
        projectiles.emplace_back(std::move(p));
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            window.close();
    }
    //Only for testing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        window.close();
    }
}


void Game::update(sf::Time& dt) {
    //Movement logic

    static sf::Clock bossSpawnClock;

    // Defaulting direction to {0,0}
    player.setDirection(sf::Vector2f(0.f,0.f));



    // Setting direction based on keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.setDirectionY(-1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.setDirectionY(+1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.setDirectionX(-1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.setDirectionX(+1);


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        // if fire function is called before cooldown time it returns nullptr. This code is required to push only valid projectiles
        auto shots = player.fire();
        if (!shots.empty()) {
            handleShot(std::move(shots));
        }
    }
    if (player.getDirection() != sf::Vector2f(0.f, 0.f)) {
        player.setLastDirection(player.getDirection());
    }




    for (auto &p: projectiles) {
        p->move(dt);
    }




    player.move(sf::Vector2f(player.getDirection()) * dt.asSeconds() * player.getSpeed());


    // Damage enemies if the bullet intersects them, change hit flag to true if yes
    for (auto &p: projectiles) {
        const auto& pBody = p->getBody();
        for (auto &e: enemies) {
            if (pBody.getGlobalBounds().intersects(e->getBounds())) {
                e->takeDamage(p->getDamage());
                p->setHit(true);
            }
        }

    }


    for (auto it =enemies.begin(); it != enemies.end();){
        const auto& eBody=(*it)->getBounds();
        if(eBody.intersects(player.getBody().getGlobalBounds())){
            //division into enemy types: boss and common
            if(auto boss = dynamic_cast<EnemyBoss*>(it->get())){ //dynamic cast recognizes if enemy is a boss
                if (boss->canAttack()) { //Boss has cooldown in attack
                    player.takeDamage(boss->getDamage());
                }
            }else{
                player.takeDamage((*it)->getDamage());// Other enemies are attacking everytime
                it = enemies.erase(it);
                continue;
            }
        }
        ++it;
    }


    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect mapBounds = map.getBounds();
    sf::Vector2f fixedPos = player.getPosition();

    if (playerBounds.left < mapBounds.left)
        fixedPos.x = mapBounds.left;
    if (playerBounds.top < mapBounds.top)
        fixedPos.y = mapBounds.top;
    if (playerBounds.left + playerBounds.width > mapBounds.left + mapBounds.width)
        fixedPos.x = mapBounds.left + mapBounds.width - playerBounds.width;
    if (playerBounds.top + playerBounds.height > mapBounds.top + mapBounds.height)
        fixedPos.y = mapBounds.top + mapBounds.height - playerBounds.height;

     player.setPosition(fixedPos);


    // Enemy actualization
    for (auto& enemy : enemies){
        enemy->update(dt, player.getPosition());
        if (auto vortex = dynamic_cast<EnemyVortex*>(enemy.get())){ //If enemies are vortex then assign a pointer to the vortex variable
            sf::Vector2f repulsion = vortex->recoilForce(player.getPosition());//pushes the player away with dynamically increasing force
            player.setPosition(player.getPosition() + repulsion * dt.asSeconds()); //changing the actual position of a player
        }
    }



//************************************************************************
//                  All monsters spawner are for testing
//                  The dificult will change with the
//                  change of waves, which will be added in the future
//**************************************************************************


    // Enemy spawn every 2 seconds
    //Adding new functions to monsters spawner like more monster spawned at the same time
    if (enemyspawnClock.getElapsedTime().asSeconds() > 2.f) {
        float RandomMonsterNumber = std::rand()%3+1; //2-5 demons spawns

        for(int i=0; i < RandomMonsterNumber; i++){
            sf::Vector2f demonSpawnPos = generateSpawnPositionNear(player.getPosition(), map.getBounds(), 200.f, 400.f);
            enemies.push_back(std::make_unique<Enemy_Demon>(demonSpawnPos));
            //Vortex enemy testing - the wave logic MUST INCLUDE
            enemies.push_back(std::make_unique<EnemyVortex>(demonSpawnPos));

        }
        //MUST INCLUDE WAVE LOGIC
        //Added bat
        sf::Vector2f batSpawnPos = generateSpawnPositionNear(player.getPosition(), map.getBounds(), 200.f, 400.f);
       enemies.push_back(std::make_unique<Enemy_Bat>(batSpawnPos));

        enemyspawnClock.restart();
    }


//*****************************************************************************************
//                    Group of ghosts spawn logic
//**************************************************************************************

    if(ghostSpawnClock.getElapsedTime().asSeconds()>ghostsDelay){
        sf::FloatRect viewBounds(view.getCenter() - view.getSize()/2.f, view.getSize()); //To spawn ghost behind the view window
        int groupSize = 40 + rand() % 60; // 40 to 60 ghosts per spawn
        sf::Vector2f dir;
        float xGhostPos;
        float yGhostPos=player.getPosition().y;
        if (rand() % 2 == 0){
            dir = sf::Vector2f(1.f, 0.f);  // Group fly to the right
            xGhostPos = viewBounds.left - 100.f; //100 pixels before left view bound
        }
        else{
            dir = sf::Vector2f(-1.f, 0.f); // Group fly to the left
            xGhostPos = viewBounds.width + viewBounds.left + 100.f; //100 pixels after right view bound
        }
        for (int i=0; i<groupSize; i++) {
            //Spreading around Y and X axes
            float ySpread = static_cast<float>((rand() % 400) - 200);
            float xSpread = static_cast<float>((rand() % 600) - 300);
            sf::Vector2f spawnPos(xGhostPos + xSpread, yGhostPos + ySpread);

            enemies.push_back(std::make_unique<Enemy_GhostGroup>(spawnPos, dir));
            ghostsDelay = 30.f + static_cast<float>(rand()%15); //After spawns delay sets new value 30-45 seconds
        }


        ghostSpawnClock.restart();
    }

    if (enemyspawnClock.getElapsedTime().asSeconds() > 6.f){
        sf::Vector2f batSpawnPos = generateSpawnPositionNear(player.getPosition(), map.getBounds(), 200.f, 400.f);
        enemies.push_back(std::make_unique<Enemy_Bat>(batSpawnPos));

        enemyspawnClock.restart();
    }

    //ONLY FOR TESTING MUST INCLUDE WAVE LOGIC
    //Boss will spawn after few waves
    if (!bossSpawned && bossSpawnClock.getElapsedTime().asSeconds() > 10.f) {
        sf::Vector2f bossSpawnPos = generateSpawnPositionNear(player.getPosition(), map.getBounds(), 300.f, 500.f);
        enemies.push_back(std::make_unique<EnemyBoss>(bossSpawnPos));

        bossSpawned = true; // Only for one boss spwan
    }



//******************************       END                   **************************************8



    // Removing dead enemies and dropping exp orbs
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [&](const std::unique_ptr<Enemies>& e) {
                                     if (e->getHP() <= 0.f) {
                                         expOrbs.push_back(std::make_unique<ExpOrb>(e->getPosition(), 25.f));
                                         return true;
                                     }
                                     return false;
                                 }), enemies.end());

    expOrbs.erase(std::remove_if(expOrbs.begin(), expOrbs.end(),[&](const std::unique_ptr<ExpOrb>& orb)
                                 {
                                     if (orb->getBounds().intersects(player.getGlobalBounds())) {
                                         player.addMaxLevelTreshold(orb->getExpValue());
                                         return true;
                                     }
                                     return false;
                                 }), expOrbs.end());


    for (auto& p : projectiles) {
        if (p->distanceExceeded() || p->getHit()) {
            // Trigger the explosion
            if (p->getIsExploding()) {
                auto* exploding = dynamic_cast<ExplodingProjectile*>(p.get());
                if (exploding) {
                    float radius = exploding->getExplosionRadius();
                    sf::Vector2f explosionCenter = exploding->getPosition();
                    for (auto& e : enemies) {
                        float dist = std::hypot(explosionCenter.x - e->getPosition().x,
                                                explosionCenter.y - e->getPosition().y);
                        if (dist <= radius) {
                            e->takeDamage(exploding->getDamage());
                        }
                    }

                    // TODO sound and visual effects
                }
            }

            // Mark projectile as hit so it can be erased later
            p->setHit(true);
        }
    }

    // Check whether the projectile has not exceeded it's maximum range or hit an enemy, if yes remove it
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const std::unique_ptr<Projectile>& p)
                                     {
                                         return (p->distanceExceeded() || p->getHit());
                                     }
                                     ), projectiles.end());


    //Camera
    sf::Vector2f viewCenter = player.getPosition();
    sf::Vector2f halfView = view.getSize() / 2.f;

    if (viewCenter.x < mapBounds.left + halfView.x)
        viewCenter.x = mapBounds.left + halfView.x;
    if (viewCenter.y < mapBounds.top + halfView.y)
        viewCenter.y = mapBounds.top + halfView.y;
    if (viewCenter.x > mapBounds.left + mapBounds.width - halfView.x)
        viewCenter.x = mapBounds.left + mapBounds.width - halfView.x;
    if (viewCenter.y > mapBounds.top + mapBounds.height - halfView.y)
        viewCenter.y = mapBounds.top + mapBounds.height - halfView.y;


     hud.update(player, window);

    view.setCenter(viewCenter);
}

void Game::render()
{
    window.clear(sf::Color::Black);


    window.setView(view);
    map.draw(window);

    for (auto& enemy : enemies)
        enemy->render(window);

    for (auto& orb : expOrbs)
        orb->render(window);

    for (auto & p: projectiles) {
        window.draw(p->getBody());
    }


     //std::cout << "[DEBUG] View Center: " << view.getCenter().x << ", " << view.getCenter().y << "\n";
    //std::cout << "[DEBUG] Boss Position: " << EnemyBoss->getPosition().x << ", " << boss->getPosition().y << "\n";


    window.draw(player.getBody());


    window.setView(window.getDefaultView()); // HUD must be static and not move with the camera
    hud.draw(window);
    window.display();


}

//Generates a random position within a specified radius from the player
sf::Vector2f Game::generateSpawnPositionNear(const sf::Vector2f& playerPos, const sf::FloatRect& mapBounds, float minDist, float maxDist) {
    sf::Vector2f spawn;
    int attempts = 0;


    do {
        float angle = static_cast<float>(rand()) / RAND_MAX * 2.f * M_PI; //Minimal radius that monster spawn
        float dist = minDist + static_cast<float>(rand()) / RAND_MAX * (maxDist - minDist);

        spawn.x = playerPos.x + std::cos(angle) * dist;
        spawn.y = playerPos.y + std::sin(angle) * dist;

        attempts++;
        if (attempts > 50) break;
    } while (!map.getBounds().contains(spawn));

    return spawn;
}



