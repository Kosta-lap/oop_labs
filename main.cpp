#include <windows.h>
#include "seagame/src/game/core/game.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Game current_game = Game();
    current_game.start();
    return 0;
}