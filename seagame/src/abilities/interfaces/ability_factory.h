#ifndef OOP_ABILITY_FACTORY_H
#define OOP_ABILITY_FACTORY_H

#include "memory"
#include "functional"

#include "ability_interface.h"
#include "../../game/utils/point.h"

class AbilityFactory{
    public:
        virtual std::shared_ptr<AbilityInterface> create(Point cord = {0, 0}, std::function<void (bool)> trigger  = [](bool) {}) = 0;
        virtual std::string getName() = 0;
};


#endif