#ifndef OOP_GAME_FIELD_H
#define OOP_GAME_FIELD_H

#include "memory"
#include "vector"
#include "point.h"
#include "ship.h"
#include "ship_manager.h"
#include "field_cell.h"
#include "ability_interface.h"


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

        int getFieldWidth();
        int getFieldHeight();
        bool checkCorrectCoords(Point cords);
        FieldCell getCellInfo(Point coords);
        CellState getSellState(Point coords);

        bool checkCorrectPosition(Point coords, bool is_horizontal, int length);
        void placeShip(Ship* ship, Point coords, bool is_horizontal);
        void attackField(Point coords);
        void setAbility(std::shared_ptr<AbilityInterface> ability);
        void printField();
};


#endif
