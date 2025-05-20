#include "game.h"
#include "enemy_demon.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <cmath>
Game::Game() : window(sf::VideoMode(2400, 1500), "Window"),
    view(window.getDefaultView()), player()
{
    map.load("./assets/map/ground_stone.png", 256, 64, 64);
    view.setSize(2400,1500);
    sf::Vector2f center = map.getSize() / 2.f;

    std::cout << "MAP CENTER: " << center.x << ", " << center.y << "\n";
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


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        // if fire function is called before cooldown time it returns nullptr. This code is required to push only valid projectiles
        auto shot = player.fire();
        if (shot)
            projectiles.emplace_back(std::move(shot));
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

    // player.setPosition(fixedPos);


    // Enemy actualization
    for (auto& enemy : enemies){
        enemy->update(dt, player.getPosition());
    }

    // Enemy spawn every 2 seconds;
    if (enemyspawnClock.getElapsedTime().asSeconds() > 2.f) {
        sf::Vector2f spawnPos = generateSpawnPositionNear(player.getPosition(), map.getBounds(), 200.f, 400.f);
        enemies.push_back(std::make_unique<Enemy_Demon>(spawnPos));
        enemyspawnClock.restart();
    }

    // Removing dead enemies;
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),[](const std::unique_ptr<Enemies>& e) {
                           return e->getHP() <= 0.f;
                  }),
        enemies.end());


    // Check whether the projectile has not exceeded it's maximum range or hit an enemy, if yes remove it
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
                                     [](const std::unique_ptr<Projectile>& p){
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

    view.setCenter(viewCenter);
}

void Game::render() {
    window.clear(sf::Color::Black);
    window.setView(view);
    map.draw(window); // map must render first

    for (auto& enemy : enemies)
        enemy->render(window);


    for (auto & p: projectiles) {
        window.draw(p->getBody());
    }


    window.draw(player.getBody());

    window.display();


}

sf::Vector2f Game::generateSpawnPositionNear(const sf::Vector2f& playerPos, const sf::FloatRect& mapBounds, float minDist, float maxDist) {
    sf::Vector2f spawn;
    int attempts = 0;

    do {
        float angle = static_cast<float>(rand()) / RAND_MAX * 2.f * M_PI;
        float dist = minDist + static_cast<float>(rand()) / RAND_MAX * (maxDist - minDist);

        spawn.x = playerPos.x + std::cos(angle) * dist;
        spawn.y = playerPos.y + std::sin(angle) * dist;

        attempts++;
        if (attempts > 50) break;
    } while (!map.getBounds().contains(spawn));

    return spawn;
}



