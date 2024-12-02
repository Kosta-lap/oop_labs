#include "double_damage.h"

DoubleDamage::DoubleDamage(std::function<void (bool)> trigger): trigger_func(trigger) {}

void DoubleDamage::applyAbility(GameField &field) {
    trigger_func(true);
}