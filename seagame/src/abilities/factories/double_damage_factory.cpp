#include "double_damage_factory.h"

std::shared_ptr<AbilityInterface> DoubleDamageFactory::create(Point cords, std::function<void(bool)> trigger) {
    return std::make_shared<DoubleDamage>(trigger);
}

std::string DoubleDamageFactory::getName() {
    return "DoubleDamage";
}