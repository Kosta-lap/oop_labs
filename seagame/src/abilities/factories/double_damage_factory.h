#ifndef OOP_DOUBLE_DAMAGE_FACTORY_H
#define OOP_DOUBLE_DAMAGE_FACTORY_H

#include "../interfaces/ability_factory.h"
#include "../effects/double_damage.h"

class DoubleDamageFactory: public AbilityFactory{
    public:
        std::shared_ptr<AbilityInterface> create(Point cords, std::function<void (bool)> trigger) override;
        std::string getName() override;
};


#endif
