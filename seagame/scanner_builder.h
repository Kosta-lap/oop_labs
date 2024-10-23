#ifndef OOP_SCANNER_BUILDER_H
#define OOP_SCANNER_BUILDER_H

#include "ability_builder.h"
#include "scanner.h"

class ScannerBuilder: public AbilityBuilder {
    public:
        std::shared_ptr<AbilityInterface> create(Point cords, std::function<void (bool)> trigger) override;
        AbilityName abilityName() override;
};


#endif
