#include "game.h"
#include "enemy_demon.h"
#include "exporb.h"
#include "enemy_bat.h"
#include "enemy_ghostgroup.h"
#include "enemyboss.h"
#include "EnemyVortex.h"
#include "enemyknight.h"
#include "enemyskeleton.h"
#include "boomerang_projectile.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "bullet.h"
#include "exploding_projectile.h"
#include "axe_projectile.h"
#include "fireball_projectile.h"

Game::Game() : window(sf::VideoMode(2400, 1500), "Window"),


    view(window.getDefaultView()),ghostsDelay(static_cast<float>(rand()%15) + 30.f),  player(), isPaused(false), availableWeapons({"DoubleGun", "QuadGun", "ExplodingGun", "Axe", "Boomerang", "PiercingGun"}), frameCounter(0)

{
    map.load("./assets/map/ground_stone.png", 256, 64, 64); //Map size is 16 384 x 16 384 pixels
    font.loadFromFile("./assets/fonts/MinimalPixel.ttf");
    view.setSize(2400,1500);
    defaultView = window.getDefaultView();
    currentWaveClock.restart();
    player.setPosition(map.getSize()/2.f);
    view.setCenter(player.getPosition());
    gunSound.loadSoundEffect("gun", "./assets/Sounds/Sounds/gun.wav", 30.f, false);
    gunSound.loadSoundEffect("axe", "./assets/Sounds/Sounds/axe.wav", 30.f, false);
    Dead.loadSoundEffect("dead", "./assets/Sounds/Music/Doom.wav", 30.f, true);



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

void Game::run(){
    window.setFramerateLimit(60);
    if(!audio.playMusic("./assets/Sounds/Music/MasterOfPuppets.wav", 30.f, true)) {
        return;
    }

    clock.restart();

    while(window.isOpen()){
        sf::Time dt = clock.restart();

        handleEvents();

        if(currentState == GameState::PLAYING)
            update(dt);

        render(dt.asSeconds());


        if(currentState == GameState::EXIT)
            window.close();


        if (!isPaused) {
            update(dt);
            render(dt.asSeconds());
        }


    }
}


void Game::handleShot(std::vector<std::unique_ptr<Projectile>> v) {
    for (auto &p : v ) {
        projectiles.emplace_back(std::move(p));
    }
}

void Game::handleEvents() {
    sf::Event event;


    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            window.close();

        if (currentState == GameState::GAMEOVER){
            if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Num1)
                    currentState = GameState::EXIT;

            }
        }


    }
    //Only for testing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        window.close();
    }
}




void Game::update(sf::Time& dt) {



    int lvl = player.getLvl();
    if (lvl % 4 == 0 && lvl != last_level_weapon) {
        last_level_weapon = lvl;

        // Give player a new weapon every four levels (This is a workaround. Weapon choosing screen went beyond earlier predicted scope. Might be implemented in the future)
        switch (lvl) {
        case 4:
            player.addWeapon(std::make_unique<Axe>());         break;
        case 8:
            player.addWeapon(std::make_unique<PiercingGun>()); break;
        case 12:
            player.addWeapon(std::make_unique<DoubleGun>());   break;
        case 16:
            player.addWeapon(std::make_unique<ExplodingGun>()); break;
        case 20:
            player.addWeapon(std::make_unique<QuadGun>());     break;
        case 24:
            player.addWeapon(std::make_unique<Boomerang>());    break;
        default:
          break;
        }
    }

   // Added movement logic to Player class
    player.keyboardMovement();
   player.determineShootingDirection(dt);



    // Weapon hotkeys
    for (int i = 0; i < static_cast<int>(player.getWeapons().size()) && i < 9; ++i) {
        sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 + i);
        if (sf::Keyboard::isKeyPressed(key)) {
            player.selectWeapon(i);
        }
    }
    if (player.getHP()<= 0.f && currentState != GameState::GAMEOVER){
        currentState = GameState::GAMEOVER;
         gameOver = false;
        return;
    }

    if(currentState == GameState::PLAYING){
        player.keyboardMovement();
        player.update(dt);
        player.move(sf::Vector2f(player.getDirection()) * dt.asSeconds() * player.getSpeed());
    }




    // Superpower hotkeys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        ActionResult ar = player.getSuperPowers()[0]->activate(player.getPosition());

        meteors.reserve(meteors.size() + ar.newMeteors.size());
        for (auto& meteor : ar.newMeteors) {
            meteors.push_back(std::move(meteor));
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        ActionResult ar = player.getSuperPowers()[1]->activate(player.getPosition(), player.getLastDirection());
        if (ar.fireball_projectile) {
            projectiles.push_back(std::move(ar.fireball_projectile));
        }
    }
    if (player.getShootingDirection() != sf::Vector2f(0.f,0.f)) {
        // if fire function is called before cooldown time it returns nullptr. This code is required to push only valid projectiles
        auto shots = player.fire();
        if (!shots.empty()) {

                    gunSound.playSoundEffect("gun");



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
                                         //To show "You won!" text after killed Boss
                                         if(dynamic_cast<EnemyBoss*>(e.get())){
                                             bossKilled=true;
                                             winClock.restart();
                                             showWinText = true;
                                         }
                                         //if any enemy is killed, it drops an exp orb
                                         expOrbs.push_back(std::make_unique<ExpOrb>(e->getPosition(), 20.f));
                                         return true;
                                     }
                                     return false;
                                 }), enemies.end());
    //Removing dead enemies if they are 4000 pixels from player position
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](const std::unique_ptr<Enemies>& e){
                        //std::hypot() calculate the shortest distance from enemy to player
                      float dist = std::hypot(player.getPosition().x-e->getPosition().x, player.getPosition().y-e->getPosition().y);
                                                return dist>4000.f;}), enemies.end());

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

void Game::render(float dt)
{
    if (currentState == GameState::GAMEOVER) {
        if (!gameOver) {
            window.clear(sf::Color::Black);
            audio.stopMusic();
            Dead.playSoundEffect("dead");
            GameOver();
            window.display();
            gameOver= true;
        }
        return;
    }
    window.clear(sf::Color::Black);


    window.setView(view);
    map.draw(window);

    for (auto& enemy : enemies)
        enemy->render(window);

    for (auto& orb : expOrbs)
        orb->render(window, dt );

    for (auto& mPtr : meteors) {
        window.draw(mPtr->getSprite());
    }

    for (auto &p : projectiles) {
        // If it's axe, draw it's sprite
        if (auto axe = dynamic_cast<AxeProjectile*>(p.get())) {
            window.draw(axe->getSprite());
        } else if (auto boomerang = dynamic_cast<BoomerangProjectile*>(p.get())) {
            window.draw(boomerang->getSprite());
        } else if (auto f = dynamic_cast<FireballProjectile*>(p.get())) {
            window.draw(f->getSprite());
        }
        else {
            // all other projectiles
            window.draw(p->getBody());
        }
    }

    player.draw(window);
    window.setView(window.getDefaultView()); // HUD must be static and not move with the camera


    float padding = 10.f;
    float yOffset = window.getSize().y - padding - 250.f;
    int slot = 1;

    for (auto& wptr : player.getWeapons()) {
        bool isCurrent = (wptr.get() == player.getCurrentWeapon());

        // text label
        std::string label = std::to_string(slot++) + ". " + wptr->getName();
        sf::Text weaponText(label, hud.getFont(), 24);
        weaponText.setFillColor(isCurrent ? sf::Color::Yellow : sf::Color::White);

        // position text
        auto tb = weaponText.getLocalBounds();
        float tx = window.getSize().x - tb.width - padding -250.f;
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


    float superPowerYOffset = window.getSize().y - padding - 300.f;


    for (auto& spw : player.getSuperPowers()) {
       // std::string label = std::to_string(spSlot++) + ". " + spw->getName();
        std::string label = "R. " + spw->getName();
        sf::Text superText(label, hud.getFont(), 24);
        superText.setFillColor(sf::Color::Cyan);

        auto tb = superText.getLocalBounds();
        float tx = padding + 250.f;
        float ty = superPowerYOffset - tb.height+ 50.f;
        superText.setPosition(tx, ty);

        // Sprite icon
        sf::Sprite icon;
        icon.setTexture(spw->getIcon());
        icon.setScale(1.5f, 1.5f);

        auto ib = icon.getGlobalBounds();
        icon.setPosition(tx, ty - ib.height - 5.f);

        window.draw(icon);
        window.draw(superText);

        superPowerYOffset -= std::max(tb.height, ib.height) + padding;
    }

    //The victory text after killing boss
    if (showWinText && winClock.getElapsedTime().asSeconds() < 5.f) {
        winText.setFont(font);
        winText.setString("YOU WON!");
        winText.setCharacterSize(100);
        winText.setFillColor(sf::Color::Yellow);

        sf::FloatRect bounds = winText.getLocalBounds();
        winText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        winText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

        window.draw(winText);
    } else if (showWinText) {
        showWinText = false;
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
    currentWave = elapsed/30 + 1;


    if(enemies.size() > 600) return;

    // Enemeis spawn in shorter period of time for each wave
    if (enemyspawnClock.getElapsedTime().asSeconds() >= std::max(0.7f, 1.8f - currentWave * 0.8f)){
        int enemyCount = 2 + rand() % 3;
        sf::Vector2f spawnPos = generateSpawnPositionNear(player.getPosition(), map.getBounds(), 900.f, 1300.f);

        static int lastWave = 0;
        if (currentWave > lastWave){
            for(auto& e : enemies){
                //for every wave the enemies are stronger and have more HP
                e->setDamage(e->getDamage()*1.2);
                e->setHP(e->getHP()*1.2);
                if(auto Demon = dynamic_cast<Enemy_Demon*>(e.get()))
                {
                    Demon->setHP(Demon->getHP()*1.1f);
                    Demon->setSpeed(Demon->getSpeed()*1.2);
                }
            }

            lastWave = currentWave;
        }

        for (int i=0; i<enemyCount; i++){
            sf::Vector2f offset = spawnPos + sf::Vector2f(rand()%600-400, rand()%600-400);

            if (currentWave == 1){
                enemies.push_back(std::make_unique<Enemy_Demon>(offset));
            }
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
                enemies.push_back(std::make_unique<EnemyVortex>(offset));
                enemies.push_back(std::make_unique<EnemyKnight>(offset));
                enemies.push_back(std::make_unique<Enemy_Demon>(offset));
            }
            else if(currentWave == 6){
                enemies.push_back(std::make_unique<EnemyVortex>(offset));
                enemies.push_back(std::make_unique<EnemyKnight>(offset));
                enemies.push_back(std::make_unique<EnemySkeleton>(offset));
                enemies.push_back(std::make_unique<Enemy_Demon>(offset));
            }
            else if(currentWave == 7){
                enemies.push_back(std::make_unique<EnemyVortex>(offset));
                enemies.push_back(std::make_unique<EnemyKnight>(offset));
                enemies.push_back(std::make_unique<Enemy_Bat>(offset));
                enemies.push_back(std::make_unique<Enemy_Demon>(offset));

            }
            else if(currentWave == 8){
                enemies.push_back(std::make_unique<EnemyVortex>(offset));
                enemies.push_back(std::make_unique<EnemyKnight>(offset));
                enemies.push_back(std::make_unique<EnemyKnight>(offset));
                enemies.push_back(std::make_unique<EnemySkeleton>(offset));
                enemies.push_back(std::make_unique<EnemySkeleton>(offset));

            }
            else if(currentWave == 9){
                enemies.push_back(std::make_unique<Enemy_Bat>(offset));
                enemies.push_back(std::make_unique<Enemy_Demon>(offset));
                enemies.push_back(std::make_unique<EnemyVortex>(offset));
                enemies.push_back(std::make_unique<EnemySkeleton>(offset));
                enemies.push_back(std::make_unique<Enemy_GhostGroup>(offset, player.getPosition() + offset));


            }
            else if(currentWave == 10){
                enemies.push_back(std::make_unique<Enemy_Bat>(offset));
                enemies.push_back(std::make_unique<Enemy_Demon>(offset));
                enemies.push_back(std::make_unique<EnemyVortex>(offset));
                enemies.push_back(std::make_unique<EnemySkeleton>(offset));
                enemies.push_back(std::make_unique<Enemy_GhostGroup>(offset, player.getPosition()+offset));
                enemies.push_back(std::make_unique<EnemyKnight>(offset));
            }
            else{
                enemies.push_back(std::make_unique<Enemy_Bat>(offset));
                enemies.push_back(std::make_unique<Enemy_Demon>(offset));
                enemies.push_back(std::make_unique<EnemyVortex>(offset));
                enemies.push_back(std::make_unique<EnemySkeleton>(offset));
                enemies.push_back(std::make_unique<Enemy_GhostGroup>(offset, player.getPosition()+offset));
                enemies.push_back(std::make_unique<EnemyKnight>(offset));
            }



        }

        enemyspawnClock.restart();
    }
    // Boss spawn at wave 10
    if (currentWave==10 && !bossSpawned){
        sf::Vector2f bossSpawn=generateSpawnPositionNear(player.getPosition(), map.getBounds(), 1000.f, 1300.f);
        enemies.push_back(std::make_unique<EnemyBoss>(bossSpawn));
        bossSpawned = true;
    }



    if (ghostSpawnClock.getElapsedTime().asSeconds() >= ghostR){

        int ghostCount = 15+rand()%30; // Ghosts
        int dirX = (rand()%2==0) ? -1 : 1;


        sf::Vector2f direction = sf::Vector2f(static_cast<float>(dirX), 0.f);

        sf::Vector2f baseSpawn = generateSpawnPositionNear(player.getPosition(), map.getBounds(), 600.f, 800.f);

        for (int i = 0; i < ghostCount; ++i) {
            float offsetX = static_cast<float>(i*30+rand()%30); // Random scatter of points around the axis X
            float offsetY = static_cast<float>((rand()%50)-50);  // Random scatter of points around the axis Y

            sf::Vector2f spawnOffset = baseSpawn + sf::Vector2f(offsetX * dirX, offsetY);
            enemies.push_back(std::make_unique<Enemy_GhostGroup>(spawnOffset, direction));
        }

        ghostSpawnClock.restart();
        ghostR = 5 + rand() % 10; // Group of ghosts spawn from 30 to 60
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
                if (event.key.code == sf::Keyboard::Num1){
                    isPaused = false;
                    currentState = GameState::PLAYING;
                }
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




void Game::GameOver(){
    static sf::Texture gameOverTexture;
    static sf::Sprite gameOverSprite;
    static sf::Font font;
    static sf::Text text;
    static bool initialized = false;

    //Game Over background loadding and font loading
    if (!initialized) {
        if (!gameOverTexture.loadFromFile("assets/Background/GameOver.png")) {
            return;
        }
        gameOverSprite.setTexture(gameOverTexture);
        gameOverSprite.setScale(static_cast<float>(window.getSize().x)/gameOverTexture.getSize().x,static_cast<float>(window.getSize().y) / gameOverTexture.getSize().y);

        if (!font.loadFromFile("assets/fonts/MinimalPixel.ttf")) {
            return;
        }

        text.setFont(font);
        text.setString("1. Get away...");
        text.setCharacterSize(48);
        text.setFillColor(sf::Color::Red);
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        text.setPosition(window.getSize().x / 2.f, window.getSize().y * 0.8f);

        initialized = true;
    }

    //Little darkening
    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));


    window.draw(gameOverSprite);
    window.draw(overlay);
    window.draw(text);

}


// This function is not being used right now, but in the future it can be adjusted to work. Right now it gives duplicate weapons. Fix required
void Game::showWeaponChoiceScreen() {
    isPaused = true;

    // Get list of all available weapons
    std::vector<std::string> allWeapons = {"DoubleGun", "QuadGun", "ExplodingGun", "Axe", "Boomerang", "PiercingGun"};

    // list of weapons player doesn't have yet
    std::vector<std::string> missingWeapons;
    for (const auto& weaponName : allWeapons) {
        bool hasWeapon = false;
        for (const auto& ownedWeapon : player.getWeapons()) {
            if (ownedWeapon->getName() == weaponName) {
                hasWeapon = true;
                break;
            }
        }
        if (!hasWeapon) {
            missingWeapons.push_back(weaponName);
        }
    }

    // If no missing weapons, return
    if (missingWeapons.empty()) {
        isPaused = false;
        return;
    }

    // If only one missing weapon, give it automatically
    if (missingWeapons.size() == 1) {
        player.addWeapon(WeaponFactory::createByName(missingWeapons[0]));
        isPaused = false;
        return;
    }

    // Select two distinct random weapons from missing weapons
    std::srand(std::time(nullptr));
    int idx1 = std::rand() % missingWeapons.size();
    int idx2;
    do {
        idx2 = std::rand() % missingWeapons.size();
    } while (idx2 == idx1);

    auto w1 = WeaponFactory::createByName(missingWeapons[idx1]);
    auto w2 = WeaponFactory::createByName(missingWeapons[idx2]);

    sf::Sprite s1{ w1->getTexture() };
    sf::Sprite s2{ w2->getTexture() };
    s1.setScale(4.f, 4.f);
    s2.setScale(4.f, 4.f);
    float centerX = window.getSize().x / 2.f;
    float iconY   = window.getSize().y * 0.35f;
    s1.setPosition(centerX - s1.getGlobalBounds().width - 30.f, iconY);
    s2.setPosition(centerX +  30.f,                      iconY);

    const sf::Font& font = hud.getFont();
    sf::Text header("Choose Your New Weapon", font, 48);
    header.setFillColor(sf::Color::White);
    header.setPosition(
        (window.getSize().x - header.getLocalBounds().width) / 2.f,
        window.getSize().y * 0.15f
        );

    sf::Text t1("1", font, 48), t2("2", font, 48);
    t1.setPosition(
        s1.getPosition().x + s1.getGlobalBounds().width/2.f - 12.f,
        iconY + s1.getGlobalBounds().height + 10.f
        );
    t2.setPosition(
        s2.getPosition().x + s2.getGlobalBounds().width/2.f - 12.f,
        iconY + s2.getGlobalBounds().height + 10.f
        );

    // Checking for an input (1/2)
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
            if (ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::Num1) {
                    player.addWeapon(std::move(w1));
                    isPaused = false;
                    clock.restart();
                    return;
                }
                if (ev.key.code == sf::Keyboard::Num2) {
                    player.addWeapon(std::move(w2));
                    isPaused = false;
                    clock.restart();
                    return;
                }
            }
        }
        window.clear(sf::Color(0,0,0,180));
        window.draw(header);
        window.draw(s1);
        window.draw(s2);
        window.draw(t1);
        window.draw(t2);
        window.display();
    }
}



