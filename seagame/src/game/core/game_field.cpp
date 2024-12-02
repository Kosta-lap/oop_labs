#include "../errors/place_error.h"
#include "../errors/out_of_bounds_error.h"
#include "game_field.h"
#include "iostream"

GameField::GameField(): GameField(0, 0) {}

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

FieldCell* GameField::getCellInfo(Point coords) {
    return &field[coords.y][coords.x];
}

CellState GameField::getSellState(Point coords){
    return field[coords.y][coords.x].cell_state;
}

void GameField::setCommand(std::shared_ptr<Command> command){
    this->addNewAbility = command;
}

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

            if (field[i][j].ship_pointer != nullptr){
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
        }
    }else{
        for (int i = 0; i < ship->getShipLength(); i++) {
            FieldCell& current_cell = field[coords.y + i][coords.x];

            current_cell.ship_pointer = ship;
            current_cell.segment_index = i;
        }
    }

}

void GameField::attackField(Point coords, bool &is_double_damage){
    if (!checkCorrectCoords(coords)) throw OutOfBoundsError("Attack out of bounds!");
    FieldCell& current_cell = field[coords.y][coords.x];
    if((current_cell.cell_state == CellState::Unknown || current_cell.cell_state == CellState::Ship) && current_cell.ship_pointer != nullptr){
        Ship* current_ship = current_cell.ship_pointer;
        current_ship->hitSegment(current_cell.segment_index, is_double_damage);
        is_double_damage = false;

        if (current_ship->isDestroyed() && this->addNewAbility != nullptr){
            this->addNewAbility->execute();
        }

        current_cell.cell_state = CellState::Ship;
    }else if(current_cell.cell_state == CellState::Unknown){
        current_cell.cell_state = CellState::Empty;
    }
}

void GameField::setAbility(std::shared_ptr<AbilityInterface> ability){
    ability->applyAbility(*this);
}

std::shared_ptr<Command> GameField::getCommand() {
    return addNewAbility;
}

void GameField::serialize(FileWrapper &file) {
    file.write(width);
    file.write(" ");
    file.write(height);
    file.write("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
           file.write(static_cast<int>(field[i][j].cell_state));
           file.write(' ');
        }
        file.write("\n");
    }
}

void GameField::deserialize(FileWrapper& file){
    int old_width, old_height;

    file.read(old_width);
    file.read(old_height);

    field.clear();
    field.assign(old_height, std::vector<FieldCell>(old_width, FieldCell {CellState::Unknown, nullptr}));
    for (int i = 0; i < old_height; i++) {
        for (int j = 0; j < old_width; j++) {
            int cellStateInt;
            file.read(cellStateInt);

            CellState cellState = static_cast<CellState>(cellStateInt);
            field[i][j].cell_state = cellState;
        }
    }
};
