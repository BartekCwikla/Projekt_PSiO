#include "game.h"
#include <SFML/Graphics.hpp>

Game::Game() : window(sf::VideoMode(2400, 1500), "Window"), view(window.getDefaultView()), player() {}

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


    player.move(sf::Vector2f(player.getDirection()) * dt.asSeconds() * player.getSpeed());

    for (auto &p: projectiles) {
        p->move(dt);
    }

    // Check whether the projectile has not exceeded it's maximum range, if yes remove it
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
                                     [](const std::unique_ptr<Projectile>& p){
                                         return p->distanceExceeded();
                                     }
                                     ), projectiles.end());
}

void Game::render() {
    window.clear(sf::Color::Black);

    window.draw(player.getBody());

    for (auto & p: projectiles) {
        window.draw(p->getBody());
    }

    window.display();


}
