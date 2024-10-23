#include "../place_error.h"
#include "../out_of_bounds_error.h"
#include "../game_field.h"
#include "iostream"

GameField::GameField(int width, int height) {
    this->width = width;
    this->height = height;

    field.assign(height, std::vector<FieldCell>(width, FieldCell {CellState::Unknown, nullptr}));
}

GameField::GameField(const GameField& other) {
    width = other.width;
    height = other.height;
    field = other.field;

}

GameField::GameField(GameField&& other) noexcept {
    width = other.width;
    height = other.height;
    field = std::move(other.field);

    other.width = 0;
    other.height = 0;

}

GameField& GameField::operator=(const GameField& other) {
    if (this == &other) {
        return *this;
    }
    width = other.width;
    height = other.height;
    field = other.field;

    return *this;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    width = other.width;
    height = other.height;
    field = std::move(other.field);
    other.width = 0;
    other.height = 0;

    return *this;
}

int GameField::getFieldWidth() {
    return this->width;
}

int GameField::getFieldHeight() {
    return this->height;
}

bool GameField::checkCorrectCoords(Point coords) {
    if (coords.x > width - 1 || coords.x < 0 || coords.y < 0 || coords.y > height - 1) return false;

    return true;
}

FieldCell GameField::getCellInfo(Point coords) {
    return field[coords.y][coords.x];
}

CellState GameField::getSellState(Point coords){
    return field[coords.y][coords.x].cell_state;
};

bool GameField::checkCorrectPosition(Point coords, bool is_horizontal, int length) {
    if (!checkCorrectCoords(coords)) return false;

    Point first_top = {coords.x - 1, coords.y - 1};
    Point second_top = {0, 0};

    if (is_horizontal){
        if (coords.x + length > width) return false;
        second_top = {coords.x + length, coords.y + 1};
    }else{
        if (coords.y + length > height) return false;
        second_top = {coords.x + 1, coords.y + length};
    }

    for (int i = first_top.y; i <= second_top.y; i++) {
        for (int j = first_top.x; j <= second_top.x; j++) {
            if (i < 0 || j < 0 || i >= height || j >= width) {continue;}

            if (field[i][j].cell_state == CellState::Ship){
                return false;
            }
        }
    }

    return true;
}

void GameField::placeShip(Ship* ship, Point coords, bool is_horizontal){
    if (!checkCorrectPosition(coords, is_horizontal, ship->getShipLength())){
        throw PlaceError("You cant place ship on this coords!");
    }


    if (is_horizontal){
        for (int i = 0; i < ship->getShipLength(); i++) {
            FieldCell& current_cell = field[coords.y][coords.x + i];

            current_cell.ship_pointer = ship;
            current_cell.segment_index = i;
            current_cell.cell_state = CellState::Ship;
        }
    }else{
        for (int i = 0; i < ship->getShipLength(); i++) {
            FieldCell& current_cell = field[coords.y + i][coords.x];

            current_cell.ship_pointer = ship;
            current_cell.segment_index = i;
            current_cell.cell_state = CellState::Ship;
        }
    }

}

void GameField::attackField(Point coords){
    if (!checkCorrectCoords(coords)) throw OutOfBoundsError("Attack out of bounds!");
    FieldCell current_cell = field[coords.y][coords.x];
    if(current_cell.cell_state == CellState::Ship){
        Ship* current_ship = current_cell.ship_pointer;
        current_ship->hitSegment(current_cell.segment_index);

    }else if(field[coords.y][coords.x].cell_state == CellState::Unknown){
        field[coords.y][coords.x].cell_state = CellState::Empty;
    }
}

void GameField::setAbility(std::shared_ptr<AbilityInterface> ability){
    ability->applyAbility(*this);
}

void GameField::printField() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (field[i][j].cell_state == CellState::Unknown){
                std::cout << "0 ";
            }else if(field[i][j].cell_state == CellState::Empty){
                std::cout << "1 ";
            }else if(field[i][j].cell_state == CellState::Ship){
                std::cout << "2 ";
            }
        }
        std::cout << "\n";
    }
}