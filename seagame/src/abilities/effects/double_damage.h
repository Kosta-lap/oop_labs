#ifndef OOP_DOUBLE_DAMAGE_H
#define OOP_DOUBLE_DAMAGE_H

#include "../interfaces/ability_interface.h"
#include "functional"
#include "../../game/core/game_field.h"
#include "../../game/utils/point.h"

class DoubleDamage: public AbilityInterface{
    private:
        std::function<void (bool)> trigger_func;

    public:
        DoubleDamage(std::function<void (bool)> trigger);

        void applyAbility(GameField &field) override;
};


#endif
