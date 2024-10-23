#include "../ability_production.h"

AbilityProduction::AbilityProduction() {
    this->double_damage_builder = std::make_shared<DoubleDamageBuilder>();
    this->scanner_builder = std::make_shared<ScannerBuilder>();
    this->random_shot_builder = std::make_shared<RandomShotBuilder>();
}

std::shared_ptr<AbilityBuilder> AbilityProduction::getBuilder(AbilityName name) {
    switch (name) {
        case AbilityName::DoubleDamage:
            return double_damage_builder;
        case AbilityName::Scanner:
            return scanner_builder;
        case AbilityName::RandomShot:
            return random_shot_builder;
    }
}
