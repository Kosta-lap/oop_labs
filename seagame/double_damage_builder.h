#ifndef OOP_DOUBLE_DAMAGE_BUILDER_H
#define OOP_DOUBLE_DAMAGE_BUILDER_H

#include "ability_builder.h"
#include "double_damage.h"

class DoubleDamageBuilder: public AbilityBuilder{
    public:
        std::shared_ptr<AbilityInterface> create(Point cords, std::function<void (bool)> trigger) override;
        AbilityName abilityName() override;
};


#endif
