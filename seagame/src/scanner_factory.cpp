#include "../scanner_factory.h"

std::shared_ptr<AbilityInterface> ScannerFactory::create(Point cords, std::function<void(bool)> trigger) {
    return std::make_shared<Scanner>(cords, trigger);
}

AbilityName ScannerFactory::abilityName() {
    return AbilityName::Scanner;
}