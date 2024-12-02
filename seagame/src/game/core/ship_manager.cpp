#include "ship_manager.h"
#include "stdexcept"

ShipManager::ShipManager(int count, std::vector<int> ships_lengths) {
   this->shipsCount = count;
    for (int i = 0; i < shipsCount; ++i) {
        Ship* ship = new Ship(ships_lengths[i]);
        this->ships.push_back(ship);
    }
}

ShipManager::ShipManager(): ShipManager(0, {}) {}

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

bool ShipManager::allAreDestroyed(){
    bool all_destroyed = true;
    for(auto ship: ships){
        if (!ship->isDestroyed()){
            all_destroyed = false;
        }
    }
    return all_destroyed;
}

int ShipManager::getShipCount() {
    return shipsCount;
}

void ShipManager::serialize(FileWrapper& file){
    file.write(shipsCount);
    file.write('\n');

    for (int i = 0; i < shipsCount; ++i) {
        file.write(ships[i]->getShipLength());
        file.write(' ');
    }
    file.write('\n');

    for (int i = 0; i < shipsCount; i++) {
        for (int j = 0; j < ships[i]->getShipLength(); ++j) {
            file.write(static_cast<int>(ships[i]->getSegment(j)));
            file.write(' ');
        }
        file.write('\n');
    }
}

void ShipManager::deserialize(FileWrapper& file){
    int new_ships_count;
    file.read(new_ships_count);

    for (auto ship: ships) {
        delete  ship;
    }
    ships.clear();
    shipsCount = new_ships_count;

    std::vector<int> shipLengths(shipsCount);
    for (int i = 0; i < shipsCount; ++i) {
        file.read(shipLengths[i]);
    }

    for (int i = 0; i < shipsCount; ++i) {
        Ship* ship = new Ship(shipLengths[i]);
        for (int j = 0; j < shipLengths[i]; ++j) {
            int segmentStateInt;
            file.read(segmentStateInt);

            SegmentState segmentState = static_cast<SegmentState>(segmentStateInt);
            ship->setSegment(j, segmentState);
        }

        ships.push_back(ship);
    }
}