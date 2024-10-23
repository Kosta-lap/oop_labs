#ifndef OOP_ABILITY_PRODUCTION_H
#define OOP_ABILITY_PRODUCTION_H

#include "ability_builder.h"
#include "double_damage_builder.h"
#include "scanner_builder.h"
#include "random_shot_builder.h"

class AbilityProduction {
    public:
        AbilityProduction();

        std::shared_ptr<AbilityBuilder> getBuilder(AbilityName name);
    private:
        std::shared_ptr<DoubleDamageBuilder> double_damage_builder;
        std::shared_ptr<ScannerBuilder> scanner_builder;
        std::shared_ptr<RandomShotBuilder> random_shot_builder;
};


#endif
