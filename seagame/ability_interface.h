#ifndef OOP_ABILITY_INTERFACE_H
#define OOP_ABILITY_INTERFACE_H

#include "iostream"
#include "ability_name.h"

class GameField;

class AbilityInterface {
    public:
        virtual void applyAbility(GameField &field) = 0;
        virtual AbilityName getName() = 0;
};


#endif
