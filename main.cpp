#include <iostream>
#include "seagame/game_field.h"
#include "seagame/ship_manager.h"


int main() {
    std::vector<int> ship_length = {2, 4};

    GameField game_field = GameField(5, 5);
    ShipManager ship_manager = ShipManager(2, ship_length);

    Ship* first = ship_manager.getShip(0);
    Ship* second = ship_manager.getShip(1);

    game_field.placeShip(first, {0, 0}, true);
    game_field.placeShip(second, {0, 2}, true);

    game_field.printField();
    game_field.attackField({0, 0});
    game_field.attackField({1, 0});
    game_field.attackField({0, 2});
    game_field.attackField({1, 2});


    return 0;
}
