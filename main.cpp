#include <SFML/Graphics.hpp>
#include "game.h"
#include <cstdlib>
#include <ctime>


int main() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Game* GameObj = new Game();


    while (GameObj->isWindowOpen()) {
        GameObj->setState(GameState::MENU);
        GameObj->showMenu();

        if (GameObj->getState() == GameState::PLAYING) {
            GameObj->run();
        }
        else if (GameObj->getState() == GameState::EXIT) {
            break;
        }
    }

    delete GameObj;

    return 0;
}
