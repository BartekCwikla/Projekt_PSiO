#include <SFML/Graphics.hpp>
#include "game.h"
#include <cstdlib>
#include <ctime>


int main() {
    std::srand(std::time(NULL)); //To randomize monster spawner

    Game* GameObj = new Game();
    GameObj->run();
    delete GameObj;
    return 0;
}
