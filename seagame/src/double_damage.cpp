#include "../double_damage.h"

DoubleDamage::DoubleDamage(Point coordinates) : coords(coordinates) {}

void DoubleDamage::applyAbility(GameField &field) {
    field.attackField(coords);
    field.attackField(coords);
}

AbilityName DoubleDamage::getName() {
    return AbilityName::DoubleDamage;
}