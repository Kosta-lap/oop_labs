#include "random_shot.h"

void RandomShot::applyAbility(GameField &field) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<Point> ship_cells;

    for (int i = 0; i < field.getFieldHeight(); ++i) {
        for (int j = 0; j < field.getFieldWidth(); ++j) {
            if(field.getCellInfo({j, i})->ship_pointer != nullptr){
                ship_cells.push_back({j, i});
            }
        }
    }

    std::uniform_int_distribution<> random_index(0, ship_cells.size() - 1);
    Point coords_for_shot = ship_cells[random_index(gen)];

    bool is_dd = false;
    field.attackField(coords_for_shot, is_dd);
    field.getCellInfo(coords_for_shot)->cell_state = CellState::Unknown;
}