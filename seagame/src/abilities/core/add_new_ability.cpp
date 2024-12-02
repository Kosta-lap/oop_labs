#include "add_new_ability.h"

AddNewAbility::AddNewAbility(AbilityManager &ability_manager) : ability_manager(ability_manager) {}

void AddNewAbility::execute() {
    this->ability_manager.produceAbility();
}
