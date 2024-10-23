#include <iostream>
#include "seagame/game_field.h"
#include "seagame/ship_manager.h"
#include "seagame/place_error.h"
#include "seagame/out_of_bounds_error.h"
#include "seagame/ability_extract_error.h"
#include "seagame/ability_manager.h"


int main() {
    std::vector<int> ship_length = {2, 4, 3};

    GameField game_field = GameField(5, 5);
    ShipManager ship_manager = ShipManager(3, ship_length);

    Ship* first = ship_manager.getShip(0);
    Ship* second = ship_manager.getShip(1);
    Ship* third = ship_manager.getShip(2);

    try{
        game_field.attackField({100, 100});
    }catch (OutOfBoundsError &err){
        std::cerr << "Error: " << err.what() << "\n";
    }

    try{
        game_field.placeShip(first, {0, 0}, true);
        game_field.placeShip(second, {0, 2}, true);
        game_field.placeShip(third, {0, 3}, true);
    }catch (PlaceError &err){
        std::cerr << "Error: " << err.what() << "\n";
    }


    game_field.printField();
    AbilityManager a_manager;

    for (int i = 0; i < 4; ++i) {
        std::shared_ptr<AbilityBuilder> ab;
        try{
            ab = a_manager.extractAbility();
            std::cout << "Ability " << i << ": " << (ab->abilityName() == AbilityName::DoubleDamage ? "DoubleDamage" : ab->abilityName() == AbilityName::Scanner ? "Scanner" : "RandomShot") << "\n";
        }catch(AbilityExtractError(& err)){
            std::cerr<<"Error: " << err.what() << "\n";
        }
    }
    std::cout << "\n";

    a_manager.produceAbility(AbilityName::Scanner);

    bool flag = false;
    game_field.setAbility(a_manager.extractAbility()->create({3, 2}, [&flag](bool is_there_ship){flag = is_there_ship;}));
    if(flag){
        std::cout << "ship is detected" << "\n";
    }else{
        std::cout << "ship is not detected" << "\n";
    }
    std::cout << "\n";

    a_manager.produceAbility(AbilityName::DoubleDamage);
    game_field.setAbility(a_manager.extractAbility()->create({0, 0}));

    a_manager.produceAbility(AbilityName::RandomShot);
    game_field.setAbility(a_manager.extractAbility()->create());



    first->printShipSegments();
    std::cout << "\n";
    second->printShipSegments();

    return 0;
}
