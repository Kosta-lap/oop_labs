#ifndef OOP_SCANNER_FACTORY_H
#define OOP_SCANNER_FACTORY_H

#include "ability_factory.h"
#include "scanner.h"

class ScannerFactory: public AbilityFactory {
    public:
        std::shared_ptr<AbilityInterface> create(Point cords, std::function<void (bool)> trigger) override;
        AbilityName abilityName() override;
};


#endif
