#ifndef OOP_PRINTER_H
#define OOP_PRINTER_H

#include "../core/game_field.h"

class Printer {
    public:
        Printer() = default;
        void printBattleField(GameField& player_gf, GameField& enemy_gf);
};


#endif