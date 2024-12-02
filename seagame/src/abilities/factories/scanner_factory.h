#ifndef OOP_SCANNER_FACTORY_H
#define OOP_SCANNER_FACTORY_H

#include "../interfaces/ability_factory.h"
#include "../effects/scanner.h"

class ScannerFactory: public AbilityFactory {
    public:
        std::shared_ptr<AbilityInterface> create(Point cords, std::function<void (bool)> trigger) override;
        std::string getName() override;

};


#endif
