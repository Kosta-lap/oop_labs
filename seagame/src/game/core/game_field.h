#ifndef OOP_GAME_FIELD_H
#define OOP_GAME_FIELD_H

#include "memory"
#include "vector"
#include "../utils/point.h"
#include "ship.h"
#include "ship_manager.h"
#include "../utils/field_cell.h"
#include "../../abilities/interfaces/ability_interface.h"
#include "../../common/command.h"


class GameField {
    private:
        int width;
        int height;
        std::vector<std::vector<FieldCell>> field;

        std::shared_ptr<Command> addNewAbility;

    public:
        GameField();
        GameField(int width, int height);
        GameField(const GameField& other);
        GameField(GameField&& other) noexcept;

        GameField& operator=(const GameField& other);
        GameField& operator=(GameField&& other) noexcept;

        int getFieldWidth();
        int getFieldHeight();
        bool checkCorrectCoords(Point cords);
        FieldCell* getCellInfo(Point coords);
        CellState getSellState(Point coords);

        void setCommand(std::shared_ptr<Command> command);
        std::shared_ptr<Command> getCommand();

        bool checkCorrectPosition(Point coords, bool is_horizontal, int length);
        void placeShip(Ship* ship, Point coords, bool is_horizontal);
        void attackField(Point coords, bool &is_double_damage);
        void setAbility(std::shared_ptr<AbilityInterface> ability);

        void serialize(FileWrapper& file);
        void deserialize(FileWrapper& file);
};


#endif
