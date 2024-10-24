#ifndef OOP_ADD_NEW_ABILITY_H
#define OOP_ADD_NEW_ABILITY_H

#include "command.h"
#include "ability_manager.h"

class AddNewAbility: public Command{
    public:
        AddNewAbility(AbilityManager& ability_manager);
        void execute() override;

    private:
        AbilityManager &ability_manager;
};

#endif
