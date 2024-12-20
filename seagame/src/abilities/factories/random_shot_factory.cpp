#include "random_shot_factory.h"

std::shared_ptr<AbilityInterface> RandomShotFactory::create(Point cords, std::function<void(bool)> trigger) {
    return std::make_shared<RandomShot>();
}

std::string RandomShotFactory::getName() {
    return "RandomShot";
}