#ifndef OOP_ABILITY_INTERFACE_H
#define OOP_ABILITY_INTERFACE_H

#include "iostream"

class GameField;

class AbilityInterface {
    public:
        virtual void applyAbility(GameField &field) = 0;
};


#endif
