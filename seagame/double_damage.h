#ifndef OOP_DOUBLE_DAMAGE_H
#define OOP_DOUBLE_DAMAGE_H

#include "ability_interface.h"
#include "game_field.h"
#include "point.h"

class DoubleDamage: public AbilityInterface{
    private:
        Point coords;

    public:
        DoubleDamage(Point coordinates);

        void applyAbility(GameField &field) override;
        AbilityName getName() override;
};


#endif
