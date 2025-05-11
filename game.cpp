#include "game.h"
#include <SFML/Graphics.hpp>



Game::Game() : window(sf::VideoMode(2400, 1500), "Window"), view(window.getDefaultView()) {}

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
        if (event.type == sf::Event::Closed)
            window.close();
    }
}


void Game::update(sf::Time& dt) {

}

void Game::render() {
    window.clear(sf::Color::Black);
    window.display();
}
