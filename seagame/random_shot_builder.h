#ifndef OOP_RANDOM_SHOT_BUILDER_H
#define OOP_RANDOM_SHOT_BUILDER_H

#include "ability_builder.h"
#include "random_shot.h"

class RandomShotBuilder: public AbilityBuilder {
    public:
        std::shared_ptr<AbilityInterface> create(Point cords, std::function<void (bool)> trigger) override;
        AbilityName abilityName() override;
};


#endif
