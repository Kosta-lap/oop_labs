#include "../random_shot.h"

void RandomShot::applyAbility(GameField &field) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<Point> ship_cells;

    for (int i = 0; i < field.getFieldHeight(); ++i) {
        for (int j = 0; j < field.getFieldWidth(); ++j) {
            if(field.getSellState({j, i}) == CellState::Ship){
                ship_cells.push_back({j, i});
            }
        }
    }

    std::uniform_int_distribution<> random_index(0, ship_cells.size() - 1);
    Point coords_for_shot = ship_cells[random_index(gen)];

    FieldCell* chosen_segment = field.getCellInfo(coords_for_shot);
    field.attackField(coords_for_shot);

    chosen_segment->cell_state = CellState::Unknown;
}

AbilityName RandomShot::getName() {
    return AbilityName::RandomShot;
}