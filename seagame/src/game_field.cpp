#include "../game_field.h"
#include "iostream"

GameField::GameField(int width, int height) {
    this->width = width;
    this->height = height;

    field.assign(height, std::vector<SellState>(width, SellState::Unknown));
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

bool GameField::checkCorrectPosition(Point coords, bool is_horizontal, int length) {
    if (coords.x > width - 1 || coords.x < 0 || coords.y < 0 || coords.y > height - 1) return false;

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

            if (field[i][j] == SellState::Ship){
                return false;
            }
        }
    }

    return true;
}

void GameField::placeShip(Ship* ship, Point coords, bool is_horizontal){
    if (!checkCorrectPosition(coords, is_horizontal, ship->getShipLength())){
        throw std::invalid_argument("You cant place ship on this coords!");
    }

    if (is_horizontal){
        for (int i = 0; i < ship->getShipLength(); i++) {
            field[coords.y][coords.x + i] = SellState::Ship;
        }
    }else{
        for (int i = 0; i < ship->getShipLength(); i++) {
            field[coords.y + i][coords.x] = SellState::Ship;
        }
    }

    ship->setShipSpec(coords, is_horizontal);
}

void GameField::attackField(Point coords, ShipManager* manager){
    if(field[coords.y][coords.x] == SellState::Ship){
        for (int ship_index = 0; ship_index < manager->getShipCount(); ship_index++) {
            Ship* current_ship = manager->getShip(ship_index);
            Point ship_coords = current_ship->getCoordinates();
            int length = current_ship->getShipLength();

            if (current_ship->getIsHorizontal()){
                if (coords.y == ship_coords.y && coords.x >= ship_coords.x && coords.x < ship_coords.x + length){
                    int segmentIndex = coords.x - ship_coords.x;
                    manager->hitShip(ship_index, segmentIndex);
                }
            }else{
                if (coords.x == ship_coords.x && coords.y >= ship_coords.y && coords.y < ship_coords.y + length){
                    int segmentIndex = coords.y - ship_coords.y;
                    manager->hitShip(ship_index, segmentIndex);
                }
            }

        }
    }else if(field[coords.y][coords.x] == SellState::Unknown){
        field[coords.y][coords.x] = SellState::Empty;
    }
}

void GameField::setShips(ShipManager* manager){
    for (int i = 0; i < manager->getShipCount(); ++i) {
        Point ship_coords{};
        bool is_horizontal;
        std::cin >> ship_coords.x >> ship_coords.y >> is_horizontal;
        placeShip(manager->getShip(i), ship_coords, is_horizontal);
    }
}

void GameField::printField() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (field[i][j] == SellState::Unknown){
                std::cout << "0 ";
            }else if(field[i][j] == SellState::Empty){
                std::cout << "1 ";
            }else if(field[i][j] == SellState::Ship){
                std::cout << "2 ";
            }
        }
        std::cout << "\n";
    }
}