#include "../ship_manager.h"
#include "stdexcept"

ShipManager::ShipManager(int count, std::vector<int> ships_lengths) {
   this->shipsCount = count;
    for (int i = 0; i < shipsCount; ++i) {
        Ship* ship = new Ship(ships_lengths[i]);
        this->ships.push_back(ship);
    }
}

ShipManager::~ShipManager() {
    for (auto ship: ships) {
        delete  ship;
    }
}

Ship* ShipManager::getShip(int ship_index) {
    if (ship_index < 0 || ship_index >= ships.size()) {
        throw std::invalid_argument("Invalid ship index");
    }
    return ships[ship_index];
}