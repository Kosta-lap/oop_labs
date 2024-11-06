#include "../ability_production.h"

AbilityProduction::AbilityProduction() {
    this->double_damage_factory = std::make_shared<DoubleDamageFactory>();
    this->scanner_factory = std::make_shared<ScannerFactory>();
    this->random_shot_factory = std::make_shared<RandomShotFactory>();
}

std::shared_ptr<AbilityFactory> AbilityProduction::getFactory(AbilityName name) {
    switch (name) {
        case AbilityName::DoubleDamage:
            return double_damage_factory;
        case AbilityName::Scanner:
            return scanner_factory;
        case AbilityName::RandomShot:
            return random_shot_factory;
    }
}
