#include <iostream>
#include "seagame/game_field.h"
#include "seagame/ship_manager.h"


int main() {
    std::vector<int> ship_length = {2, 4};

    GameField game_field = GameField(5, 5);
    ShipManager ship_manager = ShipManager(2, ship_length);

    game_field.setShips(&ship_manager);
    game_field.printField();
    std::cout << "\n";

    game_field.attackField({1, 1}, &ship_manager);
    game_field.attackField({0, 0}, &ship_manager);
    std::cout << "\n";

    game_field.attackField({0, 2}, &ship_manager);
    game_field.printField();

    return 0;
}
