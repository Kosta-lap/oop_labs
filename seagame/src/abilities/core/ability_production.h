#ifndef OOP_ABILITY_PRODUCTION_H
#define OOP_ABILITY_PRODUCTION_H

#include "../interfaces/ability_factory.h"
#include "../factories/double_damage_factory.h"
#include "../factories/scanner_factory.h"
#include "../factories/random_shot_factory.h"

class AbilityProduction {
    public:
        AbilityProduction();

        std::shared_ptr<AbilityFactory> getFactory(int index);
        int getAbilitiesQuantity();
    private:
        std::vector<std::shared_ptr<AbilityFactory>> abilities_factories;
};


#endif
