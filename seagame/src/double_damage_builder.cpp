#include "../double_damage_builder.h"

std::shared_ptr<AbilityInterface> DoubleDamageBuilder::create(Point cords, std::function<void(bool)> trigger) {
    return std::make_shared<DoubleDamage>(cords);
}

AbilityName DoubleDamageBuilder::abilityName() {
    return AbilityName::DoubleDamage;
}