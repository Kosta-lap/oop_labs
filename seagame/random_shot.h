#ifndef OOP_RANDOM_SHOT_H
#define OOP_RANDOM_SHOT_H

#include "ability_interface.h"
#include "game_field.h"
#include "random"

class RandomShot: public AbilityInterface{
    public:
        RandomShot() = default;

        void applyAbility(GameField &field) override;
        AbilityName getName() override;
};


#endif
