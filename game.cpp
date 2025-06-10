#include "game.h"
#include "enemy_demon.h"
#include "exporb.h"
#include "enemy_bat.h"
#include "enemy_ghostgroup.h"
#include "enemyboss.h"
#include "EnemyVortex.h"'
#include "enemyknight.h"
#include "enemyskeleton.h"
#include "boomerang_projectile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "exploding_projectile.h"
#include "axe_projectile.h"

Game::Game() : window(sf::VideoMode(2400, 1500), "Window"),
    view(window.getDefaultView()),ghostsDelay(static_cast<float>(rand()%15) + 30.f),  player(), frameCounter(0)
{
    map.load("./assets/map/ground_stone.png", 256, 64, 64); //Map size is 16 384 x 16 384 pixels
    view.setSize(2400,1500);
    defaultView = window.getDefaultView();
    currentWaveClock.restart();
    player.setPosition(map.getSize()/2.f);
    view.setCenter(player.getPosition());

}
GameState Game::getState() const{
    return this->currentState;
}
void Game::setState(GameState state){
    currentState = state;
}
bool Game::isWindowOpen() const{
    return window.isOpen();
}

void Game::run() {
    window.setFramerateLimit(60);
    if(!audio.playMusic("assets/Sounds/Music/MasterOfPuppets.wav", 30.f, true)) {
        return;
    }

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

    // Defaulting direction to {0,0}
    player.setDirection(sf::Vector2f(0.f,0.f));

    // Setting direction based on keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.setDirectionY(-1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.setDirectionY(+1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.setDirectionX(-1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.setDirectionX(+1);



    // Weapon hotkeys
    for (int i = 0; i < static_cast<int>(player.getWeapons().size()) && i < 9; ++i) {
        sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 + i);
        if (sf::Keyboard::isKeyPressed(key)) {
            player.selectWeapon(i);
        }
    }


    // Superpower hotkeys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        ActionResult ar = player.getSuperPowers()[0]->activate(player.getPosition());

        meteors.reserve(meteors.size() + ar.newMeteors.size());
        for (auto& meteor : ar.newMeteors) {
            meteors.push_back(std::move(meteor));
        }
    }
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
        if (auto boomerang = dynamic_cast<BoomerangProjectile*>(p.get())) {
            boomerang->move(dt, player.getPosition());
        } else {
            p->move(dt);
        }
    }

    for (auto& mPtr : meteors) {
        mPtr->move(dt);
    }

    player.move(sf::Vector2f(player.getDirection()) * dt.asSeconds() * player.getSpeed());

    // Damage enemies if the bullet intersects them, change hit flag to true if yes
    for (auto &p: projectiles) {
        const auto& pBody = p->getBody();
        for (auto &e: enemies) {
            if (pBody.getGlobalBounds().intersects(e->getBounds())) {
                sf::Vector2f knockDirect = p->getDirection();
                float len = std::sqrt(knockDirect.x*knockDirect.x + knockDirect.y*knockDirect.y);
                if(len!= 0.f) knockDirect /=len; // Direction vector normalization
                //Hit effects:
                e->applyKnockback(knockDirect, 600.f); // force of knockback
                e->flashHit(0.15f); // time duration of white flash
                e->takeDamage(p->getDamage());
                if (!(p->getIsPiercing())){
                    p->setHit(true);
                }

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

    EnemiesBoundsColision();
    wavesLogic();

    // Removing dead enemies and dropping exp orbs
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [&](const std::unique_ptr<Enemies>& e) {
                                     if (e->getHP() <= 0.f) {
                                         expOrbs.push_back(std::make_unique<ExpOrb>(e->getPosition(), 20.f));
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
            if (!(p->getIsPiercing())) {
                p->setHit(true);
            }

        }
    }


    for (auto &meteor: meteors) {
        if (meteor->getShouldExplode()) {
            auto* exploding = dynamic_cast<Meteor*>(meteor.get());
            float radius = exploding->getExplosionRadius();
            sf::Vector2f explosionCenter = exploding->getPosition();
            for (auto& e : enemies) {
                float dist = std::hypot(explosionCenter.x - e->getPosition().x,
                                        explosionCenter.y - e->getPosition().y);
                if (dist <= radius) {
                    e->takeDamage(exploding->getDamage());
                }
            }
        }
    }

    // Check whether the projectile has not exceeded it's maximum range or hit an enemy, if yes remove it
    projectiles.erase(std::remove_if(
                          projectiles.begin(),
                          projectiles.end(),
                          [&](const std::unique_ptr<Projectile>& p) {
                              if (auto boom = dynamic_cast<BoomerangProjectile*>(p.get())) {
                                  return boom->getExpired();
                              } else {
                                  return (p->distanceExceeded() || p->getHit());
                              }
                          }
                          ), projectiles.end());

    meteors.erase(
        std::remove_if(meteors.begin(), meteors.end(),
                       [&](const std::unique_ptr<Meteor>& m){
                           return m && m->getShouldExplode();
                       }
                       ),
        meteors.end()
        );


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

    hud.update(player, window, currentWave, enemyspawnClock.getElapsedTime().asSeconds());
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

    for (auto& mPtr : meteors) {
        window.draw(mPtr->getSprite());
    }

    for (auto &p : projectiles) {
        // If it's axe, draw it's sprite
        if (auto axe = dynamic_cast<AxeProjectile*>(p.get())) {
            window.draw(axe->getSprite());
        } else if (auto boomerang = dynamic_cast<BoomerangProjectile*>(p.get())) {
            window.draw(boomerang->getSprite());
        }

        else {
            // all other projectiles
            window.draw(p->getBody());
        }
    }
    window.draw(player.getBody());
    window.setView(window.getDefaultView()); // HUD must be static and not move with the camera


    float padding = 10.f;
    float yOffset = window.getSize().y - padding;
    int slot = 1;

    for (auto& wptr : player.getWeapons()) {
        bool isCurrent = (wptr.get() == player.getCurrentWeapon());

        // text label
        std::string label = std::to_string(slot++) + ". " + wptr->getName();
        sf::Text weaponText(label, hud.getFont(), 24);
        weaponText.setFillColor(isCurrent ? sf::Color::Yellow : sf::Color::White);

        // position text
        auto tb = weaponText.getLocalBounds();
        float tx = window.getSize().x - tb.width - padding;
        float ty = yOffset - tb.height;
        weaponText.setPosition(tx, ty);

        // sprite icon
        sf::Sprite icon;
        icon.setTexture(wptr->getTexture());
        icon.setScale(1.5f, 1.5f);

        auto ib = icon.getGlobalBounds();
        // setting placement of an icon to be above the text
        icon.setPosition(tx, ty - ib.height - 5.f);

        // drawing a box around the current weapon
        if (isCurrent) {
            sf::RectangleShape highlight;
            highlight.setSize({ ib.width + tb.width + 15.f, std::max(ib.height, tb.height) + 10.f });
            highlight.setFillColor(sf::Color(255, 255, 0, 50));
            highlight.setPosition(tx - ib.width - 10.f, ty - (ib.height + tb.height)/2.f);
            window.draw(highlight);
        }

        // draw sprite and text
        window.draw(icon);
        window.draw(weaponText);


        yOffset -= std::max(tb.height, ib.height) + padding;
    }


    float superPowerYOffset = window.getSize().y - padding;
    int spSlot = 1;

    for (auto& spw : player.getSuperPowers()) {
        std::string label = std::to_string(spSlot++) + ". " + spw->getName();
        sf::Text superText(label, hud.getFont(), 24);
        superText.setFillColor(sf::Color::Cyan);

        auto tb = superText.getLocalBounds();
        float tx = padding;
        float ty = superPowerYOffset - tb.height;
        superText.setPosition(tx, ty);

        // Sprite icon
        sf::Sprite icon;
        icon.setTexture(spw->getIcon());
        icon.setScale(1.5f, 1.5f);

        auto ib = icon.getGlobalBounds();
        icon.setPosition(tx, ty - ib.height - 5.f);

        // Optional: Draw highlight if this is an active superpower (if applicable)
        // if (player.getCurrentSuperPower() == spw.get()) {
        //     sf::RectangleShape highlight;
        //     highlight.setSize({ ib.width + tb.width + 15.f, std::max(ib.height, tb.height) + 10.f });
        //     highlight.setFillColor(sf::Color(0, 255, 255, 50));
        //     highlight.setPosition(tx - 5.f, ty - (ib.height + tb.height)/2.f);
        //     window.draw(highlight);
        // }

        window.draw(icon);
        window.draw(superText);

        superPowerYOffset -= std::max(tb.height, ib.height) + padding;
    }


    hud.draw(window);
    window.display();
}
//Collision enemy to enemy
void Game::EnemiesBoundsColision(){
    const float coolisionLimit = 0.1f;

    for (size_t i = 0; i < enemies.size(); ++i) {
        for (size_t j = i + 1; j < enemies.size(); ++j) {
            auto& e1 = enemies[i];
            auto& e2 = enemies[j];

            if (e1->getBounds().intersects(e2->getBounds())){
                sf::Vector2f pos1=e1->getPosition();
                sf::Vector2f pos2=e2->getPosition();
                sf::Vector2f delta=pos1 - pos2;
                float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

                if (distance == 0.f)
                    continue;

                sf::Vector2f pushDir = delta/distance;

                // Rozdzielenie o stałą wartość
                e1->setPosition(pos1 + pushDir*coolisionLimit);
                e2->setPosition(pos2 - pushDir*coolisionLimit);
            }
        }
    }
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



void Game::wavesLogic() {

    // Counting wave in relative to time
    int elapsed = static_cast<int>(waveClock.getElapsedTime().asSeconds());
    currentWave = elapsed/20 + 1;


    if (enemies.size()>200) return; //Maximum number of enemies at the screen

    // Enemeis spawn in shorter period of time for each wave
    if (enemyspawnClock.getElapsedTime().asSeconds() >= std::max(0.7f, 1.8f - currentWave * 0.7f)){
        int enemyCount = 2 + rand() % 3;
        sf::Vector2f spawnPos = generateSpawnPositionNear(player.getPosition(), map.getBounds(), 500.f, 700.f);

        for (int i=0; i<enemyCount; i++){
            sf::Vector2f offset = spawnPos + sf::Vector2f(rand()%600-400, rand()%600-400);

            if (currentWave == 1)
                enemies.push_back(std::make_unique<Enemy_Demon>(offset));
            else if (currentWave == 2){
                enemies.push_back(std::make_unique<Enemy_Bat>(offset));
                enemies.push_back(std::make_unique<Enemy_Demon>(offset));
            }
            else if (currentWave == 3){
                enemies.push_back(std::make_unique<EnemyKnight>(offset));
                enemies.push_back(std::make_unique<Enemy_Bat>(offset));

            }
            else if(currentWave == 4){
                enemies.push_back(std::make_unique<EnemySkeleton>(offset));
                enemies.push_back(std::make_unique<Enemy_Demon>(offset));
                enemies.push_back(std::make_unique<EnemyKnight>(offset));
            }
            else if(currentWave == 5){
                //enemies.push_back(std::make_unique<EnemyVortex>(offset));
                enemies.push_back(std::make_unique<EnemyKnight>(offset));
                enemies.push_back(std::make_unique<Enemy_Bat>(offset));
            }
            else {
                // Mix
                switch(rand()%5){
                case 0: enemies.push_back(std::make_unique<Enemy_Demon>(offset)); break;
                case 1: enemies.push_back(std::make_unique<Enemy_Bat>(offset)); break;
                case 2: enemies.push_back(std::make_unique<EnemyKnight>(offset)); break;
                case 3: enemies.push_back(std::make_unique<EnemySkeleton>(offset)); break;
                case 4: enemies.push_back(std::make_unique<EnemyVortex>(offset)); break;
                }
            }
        }

        enemyspawnClock.restart();
    }
    // Boss spawn at wave 10
    if (currentWave==10 && !bossSpawned){
        sf::Vector2f bossSpawn=generateSpawnPositionNear(player.getPosition(), map.getBounds(), 400.f, 600.f);
        enemies.push_back(std::make_unique<EnemyBoss>(bossSpawn));
        bossSpawned = true;
    }



    if (ghostSpawnClock.getElapsedTime().asSeconds() >= ghostR){

        int ghostCount = 20+rand()%10; // Ghosts
        int dirX = (rand()%2==0) ? -1 : 1;

        float yOffset = static_cast<float>((rand()%200) - 201);
        sf::Vector2f direction(static_cast<float>(dirX), player.getPosition().y + yOffset);

        sf::Vector2f baseSpawn = generateSpawnPositionNear(player.getPosition(), map.getBounds(), window.getSize().x-200.f, player.getPosition().y+yOffset);

        for (int i = 0; i < ghostCount; ++i) {
            float offsetX = static_cast<float>(i*30+rand()%30); // Random scatter of points around the axis X
            float offsetY = static_cast<float>((rand()%60)-30);  // Random scatter of points around the axis Y

            sf::Vector2f spawnOffset = baseSpawn + sf::Vector2f(offsetX * dirX, offsetY);
            enemies.push_back(std::make_unique<Enemy_GhostGroup>(spawnOffset, direction));
        }

        ghostSpawnClock.restart();
        ghostR = 30 + rand() % 31; // Group of ghosts spawn from 30 to 60
    }
}

void Game::showMenu() {
    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("assets/Background/Background.png")) {
        return;
    }
    sf::Sprite menuBackground(menuBackgroundTexture);

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/MinimalPixel.ttf")) {
        return;
    }

    sf::Text option1("1. ", font, 32);
    sf::Text option2("2.", font, 32);


    option1.setString("1. Start the Mayhem...");
    option2.setString("2. Get away");

    sf::FloatRect bounds1 = option1.getLocalBounds();
    option1.setOrigin(bounds1.left + bounds1.width / 2.f,
                      bounds1.top + bounds1.height / 2.f);
    option1.setPosition(window.getSize().x / 2.f, window.getSize().y * 0.65f);

    sf::FloatRect bounds2 = option2.getLocalBounds();
    option2.setOrigin(bounds2.left + bounds2.width / 2.f,
                      bounds2.top + bounds2.height / 2.f);
    option2.setPosition(window.getSize().x / 2.f, window.getSize().y * 0.75f);

    while (window.isOpen() && currentState == GameState::MENU) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1)
                    currentState = GameState::PLAYING;
                else if (event.key.code == sf::Keyboard::Num2)
                    currentState = GameState::EXIT;
            }
        }

        window.clear();
        window.draw(menuBackground);
        window.draw(option1);
        window.draw(option2);
        window.display();
    }
}
