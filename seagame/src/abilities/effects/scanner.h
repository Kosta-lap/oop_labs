#ifndef OOP_SCANNER_H
#define OOP_SCANNER_H

#include "functional"
#include "../interfaces/ability_interface.h"
#include "../../game/core/game_field.h"
#include "../../game/utils/point.h"

class Scanner:public AbilityInterface{
    private:
        Point coords;
        std::function<void (bool)> trigger_func;

    public:
        Scanner(Point coordinates, std::function<void (bool)> trigger);

        void applyAbility(GameField &field) override;
};


#endif
