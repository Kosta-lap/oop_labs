#ifndef OOP_RANDOM_SHOT_FACTORY_H
#define OOP_RANDOM_SHOT_FACTORY_H

#include "../interfaces/ability_factory.h"
#include "../effects/random_shot.h"

class RandomShotFactory: public AbilityFactory {
    public:
        std::shared_ptr<AbilityInterface> create(Point cords, std::function<void (bool)> trigger) override;
        std::string getName() override;

};


#endif
