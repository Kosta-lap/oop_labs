#ifndef OOP_GAME_STATE_H
#define OOP_GAME_STATE_H

#include "game_field.h"
#include "ship_manager.h"
#include "ship.h"
#include "../../abilities/core/ability_manager.h"
#include "../errors/place_error.h"

class GameState {
    private:
        AbilityManager* player_am;
        GameField* player_gf;
        ShipManager* player_sm;

        GameField* enemy_gf;
        ShipManager* enemy_sm;

        std::vector<Point> player_cords;
        std::vector<int> player_orient;
        std::vector<Point> enemy_cords;
        std::vector<int> enemy_orient;
    public:
        GameState();
        ~GameState();

        bool placePlayerShip(Point point, int orientation, int index);
        void placeEnemyShips();
        void useAbility(bool& is_double_damage);
        void printBattleField();
        void resetEnemy();

        int getAbilitiesCount();
        std::string getLastAbilityName();

        GameField& getPlayerField();
        GameField& getEnemyField();
        ShipManager& getPlayerShipManager();
        ShipManager& getEnemyShipManager();

        friend FileWrapper& operator<<(FileWrapper& file, const GameState& game_state);
        friend FileWrapper& operator>>(FileWrapper& file, GameState& game_state);
};


#endif
