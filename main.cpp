#include <iostream>
#include "seagame/game_field.h"
#include "seagame/ship_manager.h"
#include "seagame/double_damage.h"
#include "seagame/scanner.h"
#include "seagame/random_shot.h"
#include "seagame/ability_manager.h"


int main() {
    std::vector<int> ship_length = {2, 4};

    GameField game_field = GameField(5, 5);
    ShipManager ship_manager = ShipManager(2, ship_length);

    Ship* first = ship_manager.getShip(0);
    Ship* second = ship_manager.getShip(1);

    game_field.placeShip(first, {0, 0}, true);
    game_field.placeShip(second, {0, 2}, true);

    game_field.printField();
    AbilityManager a_manager;

    for (int i = 0; i < 3; ++i) {
        std::shared_ptr<AbilityBuilder> ab;
        ab = a_manager.extractAbility();

        std::cout << "Ability " << i << ": " << (ab->abilityName() == AbilityName::DoubleDamage ? "DoubleDamage" : ab->abilityName() == AbilityName::Scanner ? "Scanner" : "RandomShot") << "\n";
    }

    a_manager.produceAbility(AbilityName::Scanner);

    bool flag = false;
    game_field.setAbility(a_manager.extractAbility()->create({3, 2}, [&flag](bool is_there_ship){flag = is_there_ship;}));
    if(flag){
        std::cout << "ship is detected" << "\n";
    }else{
        std::cout << "ship is not detected" << "\n";
    }

    a_manager.produceAbility(AbilityName::DoubleDamage);
    game_field.setAbility(a_manager.extractAbility()->create({0, 0}));

    a_manager.produceAbility(AbilityName::RandomShot);
    game_field.setAbility(a_manager.extractAbility()->create());



    first->printShipSegments();
    std::cout << "\n";
    second->printShipSegments();

    return 0;
}
