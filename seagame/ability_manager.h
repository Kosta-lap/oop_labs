#ifndef OOP_ABILITY_MANAGER_H
#define OOP_ABILITY_MANAGER_H

#include "iostream"
#include "functional"
#include "queue"
#include "memory"

#include "ability_interface.h"
#include "ability_production.h"
#include "Point.h"

class AbilityManager {
    private:
        std::queue<std::shared_ptr<AbilityBuilder>> abilities;
        AbilityProduction abilityProduction;

    public:
        AbilityManager();

        void produceAbility(AbilityName abilityName);
        std::shared_ptr<AbilityBuilder> extractAbility();
        AbilityName font_skill();
        int queue_size();
};


#endif
