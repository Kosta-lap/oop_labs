#include <windows.h>
#include "seagame/src/game/core/game_controller.h"



int main() {
    SetConsoleOutputCP(CP_UTF8);

    Game current_game = Game();
    GameController game_control = GameController<CliInput, CliOutput, Printer>(current_game);

    game_control.play();

    return 0;
}