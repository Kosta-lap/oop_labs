#include "ability_production.h"

AbilityProduction::AbilityProduction() {
    this->abilities_factories.push_back(std::make_shared<DoubleDamageFactory>());
    this->abilities_factories.push_back(std::make_shared<ScannerFactory>());
    this->abilities_factories.push_back(std::make_shared<RandomShotFactory>());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(abilities_factories.begin(), abilities_factories.end(), gen);
}

int AbilityProduction::getAbilitiesQuantity() {
    return abilities_factories.size();
}

std::shared_ptr<AbilityFactory> AbilityProduction::getFactory(int index) {
    return abilities_factories.at(index);
}
