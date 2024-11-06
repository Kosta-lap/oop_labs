#ifndef OOP_RANDOM_SHOT_FACTORY_H
#define OOP_RANDOM_SHOT_FACTORY_H

#include "ability_factory.h"
#include "random_shot.h"

class RandomShotFactory: public AbilityFactory {
    public:
        std::shared_ptr<AbilityInterface> create(Point cords, std::function<void (bool)> trigger) override;
        AbilityName abilityName() override;
};


#endif
