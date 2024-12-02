#ifndef OOP_SHIP_MANAGER_H
#define OOP_SHIP_MANAGER_H

#include "ship.h"
#include "vector"
#include "../../common/FileWrapper.h"


class ShipManager {
    private:
        int shipsCount;
        std::vector<Ship*> ships;

    public:
        ShipManager();
        explicit ShipManager(int count, std::vector<int> ships_lengths);
        ~ShipManager();

        Ship* getShip(int ship_index);
        bool allAreDestroyed();
        int getShipCount();

        void serialize(FileWrapper& file);
        void deserialize(FileWrapper& file);
};


#endif
