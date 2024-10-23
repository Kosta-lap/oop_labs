#include "../scanner_builder.h"

std::shared_ptr<AbilityInterface> ScannerBuilder::create(Point cords, std::function<void(bool)> trigger) {
    return std::make_shared<Scanner>(cords, trigger);
}

AbilityName ScannerBuilder::abilityName() {
    return AbilityName::Scanner;
}