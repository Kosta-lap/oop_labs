#include "../ability_manager.h"
#include "../ability_extract_error.h"

AbilityManager::AbilityManager() {
    std::vector<AbilityName> random_abilities = this->getRandomAbilities();

    for (auto name:random_abilities){
        this->produceAbility(name);
    }
}

void AbilityManager::produceAbility(AbilityName abilityName) {
    this->abilities.push(this->abilityProduction.getBuilder(abilityName));
}

std::shared_ptr<AbilityBuilder> AbilityManager::extractAbility() {
    if (this->abilities.empty()) throw AbilityExtractError("No abilities available!");

    std::shared_ptr<AbilityBuilder> first_ability = this->abilities.front();
    this->abilities.pop();

    return first_ability;
}

std::vector<AbilityName> AbilityManager::getRandomAbilities() {
    std::vector<AbilityName> random_abilities = { AbilityName::DoubleDamage, AbilityName::Scanner, AbilityName::RandomShot};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(random_abilities.begin(), random_abilities.end(), gen);

    return random_abilities;
}

AbilityName AbilityManager::font_skill() {
    return this->abilities.front()->abilityName();
}

int AbilityManager::queue_size() {
    return this->abilities.size();
}