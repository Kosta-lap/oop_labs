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
        bool is_player_turn;
    public:
        Game();
        void start();
        void play();
        void newRound();

        void playerTurn(int choice);
        void enemyTurn();

        void inputPlayerData();
        int getValidInput();
};


#endif //OOP_GAME_H
