#include <SFML/Graphics.hpp>
#include "game.h"


int main() {
    Game* GameObj = new Game();
    GameObj->run();
    delete GameObj;
    return 0;
}
