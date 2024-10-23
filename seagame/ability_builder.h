#ifndef OOP_ABILITY_BUILDER_H
#define OOP_ABILITY_BUILDER_H

#include "memory"
#include "functional"

#include "ability_name.h"
#include "ability_interface.h"
#include "Point.h"

class AbilityBuilder{
    public:
        virtual std::shared_ptr<AbilityInterface> create(Point cord = {0, 0}, std::function<void (bool)> trigger  = [](bool) {}) = 0;
        virtual AbilityName abilityName() = 0;
};


#endif