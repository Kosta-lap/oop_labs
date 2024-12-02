#ifndef OOP_RANDOM_SHOT_H
#define OOP_RANDOM_SHOT_H

#include "../interfaces/ability_interface.h"
#include "../../game/core/game_field.h"
#include "random"

class RandomShot: public AbilityInterface{
    public:
        RandomShot() = default;

        void applyAbility(GameField &field) override;
};


#endif
