#include "game.h"
#include <SFML/Graphics.hpp>

Game::Game() : window(sf::VideoMode(2400, 1500), "Window"),
    view(window.getDefaultView()), player()
{
    map.load("assets/map/ground_stone.png", 256, 64, 64);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) { //Only for testing
        window.close();
    }
}


void Game::update(sf::Time& dt) {
    //Movement logic

    // Defaulting direction to {0,0}
    player.setDirection(sf::Vector2f(0,0));

    // Setting direction based on keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.setDirectionY(-1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.setDirectionY(+1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.setDirectionX(-1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.setDirectionX(+1);

    player.move(sf::Vector2f(player.getDirection()) * dt.asSeconds() * player.getSpeed());
    window.setView(view);

}

void Game::render() {
    window.clear(sf::Color::Black);
    map.draw(window); // map must render first
    window.draw(player.getBody());
    window.display();


}
