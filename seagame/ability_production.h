#ifndef OOP_ABILITY_PRODUCTION_H
#define OOP_ABILITY_PRODUCTION_H

#include "ability_factory.h"
#include "double_damage_factory.h"
#include "scanner_factory.h"
#include "random_shot_factory.h"

class AbilityProduction {
    public:
        AbilityProduction();

        std::shared_ptr<AbilityFactory> getFactory(AbilityName name);
    private:
        std::shared_ptr<DoubleDamageFactory> double_damage_factory;
        std::shared_ptr<ScannerFactory> scanner_factory;
        std::shared_ptr<RandomShotFactory> random_shot_factory;
};


#endif
