#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "iostream"
#include "game_state.h"
#include "../errors/place_error.h"

class Game {
    private:
        GameState game_state;

        int round;
        bool is_double_damage;
    public:
        Game();

        void newRound();
        void enemyTurn();

        bool isPlayerLose();
        bool isPlayerWon();
        void playerShoot(Point cords);
        void usePlayerAbility(AbilityUsageInfo& info);

        GameState& getGameState();
        int& getCurrentRound();
};


#endif
