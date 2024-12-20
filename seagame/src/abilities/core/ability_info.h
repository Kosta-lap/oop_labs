#ifndef OOP_ABILITY_INFO_H
#define OOP_ABILITY_INFO_H

#include "iostream"
#include "../../game/utils/point.h"

struct AbilityUsageInfo {
    std::string abilityName;
    Point coordinates;
    bool needsCoordinates = false;
    bool isDoubleDamage = false;
    bool randomShotPerformed = false;
    bool noAbilities = false;
    bool errorOccurred = false;
    bool resultOfScanner = false;
};

#endif
