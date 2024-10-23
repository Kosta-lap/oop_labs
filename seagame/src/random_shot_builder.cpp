#include "../random_shot_builder.h"

std::shared_ptr<AbilityInterface> RandomShotBuilder::create(Point cords, std::function<void(bool)> trigger) {
    return std::make_shared<RandomShot>();
}

AbilityName RandomShotBuilder::abilityName() {
    return AbilityName::RandomShot;
}