#ifndef OOP_GAME_FIELD_H
#define OOP_GAME_FIELD_H

#include "vector"
#include "point.h"
#include "ship.h"
#include "ship_manager.h"

enum class SellState{Unknown, Empty, Ship};

class GameField {
    private:
        int width;
        int height;
        std::vector<std::vector<SellState>> field;

    public:
        GameField(int width, int height);
        GameField(const GameField& other);
        GameField(GameField&& other) noexcept;

        GameField& operator=(const GameField& other);
        GameField& operator=(GameField&& other) noexcept;

        bool checkCorrectPosition(Point coords, bool is_horizontal, int length);
        void placeShip(Ship* ship, Point coords, bool is_horizontal);
        void attackField(Point coords, ShipManager* manager);
        void printField();
        void setShips(ShipManager* manager);
};


#endif
