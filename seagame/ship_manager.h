#ifndef OOP_SHIP_MANAGER_H
#define OOP_SHIP_MANAGER_H

#include "ship.h"
#include "vector"


class ShipManager {
    private:
        int shipsCount;
        std::vector<Ship*> ships;

    public:
        explicit ShipManager(int count, std::vector<int> ships_lengths);
        ~ShipManager();

        Ship* getShip(int ship_index);
};


#endif
