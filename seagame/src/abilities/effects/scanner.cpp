#include "scanner.h"

Scanner::Scanner(Point coordinates, std::function<void (bool)> trigger) : coords(coordinates), trigger_func(trigger) {}

void Scanner::applyAbility(GameField &field) {
    bool is_there_ship = false;
    std::vector<Point> sector {coords, {coords.x + 1, coords.y}, {coords.x, coords.y}, {coords.x + 1, coords.y + 1}};

    for(Point point : sector){
        if(field.getCellInfo(point)->ship_pointer != nullptr){
            is_there_ship = true;
            break;
        }
    }

    trigger_func(is_there_ship);
}