#ifndef OOP_GAME_FIELD_H
#define OOP_GAME_FIELD_H

#include "vector"
#include "point.h"
#include "ship.h"
#include "ship_manager.h"
#include "field_cell.h"


class GameField {
    private:
        int width;
        int height;
        std::vector<std::vector<FieldCell>> field;

    public:
        GameField(int width, int height);
        GameField(const GameField& other);
        GameField(GameField&& other) noexcept;

        GameField& operator=(const GameField& other);
        GameField& operator=(GameField&& other) noexcept;

        bool checkCorrectPosition(Point coords, bool is_horizontal, int length);
        void placeShip(Ship* ship, Point coords, bool is_horizontal);
        void attackField(Point coords);
        void printField();
};


#endif
