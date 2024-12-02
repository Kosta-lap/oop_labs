#ifndef OOP_ABILITY_MANAGER_H
#define OOP_ABILITY_MANAGER_H

#include "iostream"
#include "functional"
#include "queue"
#include "memory"

#include "../interfaces/ability_interface.h"
#include "ability_production.h"
#include "../../game/utils/point.h"

class AbilityManager {
    private:
        std::queue<std::shared_ptr<AbilityFactory>> abilities;
        AbilityProduction abilityProduction;

    public:
        AbilityManager();

        void produceAbility();
        std::shared_ptr<AbilityFactory> extractAbility();
        std::string getLastName();
        int queueSize();

        void serialize(FileWrapper& file);
        void deserialize(FileWrapper& file);
};


#endif
