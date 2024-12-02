#include "ability_manager.h"
#include "../errors/ability_extract_error.h"

AbilityManager::AbilityManager() {
    for (int i = 0; i < abilityProduction.getAbilitiesQuantity(); i++) {
        this->abilities.push(abilityProduction.getFactory(i));
    }
}

void AbilityManager::produceAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, abilityProduction.getAbilitiesQuantity() - 1);

    this->abilities.push(this->abilityProduction.getFactory(dis(gen)));
}

std::shared_ptr<AbilityFactory> AbilityManager::extractAbility() {
    if (!queueSize()) throw AbilityExtractError("No abilities available!");

    std::shared_ptr<AbilityFactory> first_ability = this->abilities.front();
    this->abilities.pop();

    return first_ability;
}

std::string AbilityManager::getLastName() {
    if (queueSize() != 0){
        std::shared_ptr<AbilityFactory> first_ability = this->abilities.front();
        return first_ability->getName();
    }else{
        return "There are no abilities!";
    }
}

int AbilityManager::queueSize() {
    return this->abilities.size();
}

void AbilityManager::serialize(FileWrapper& file){
    std::queue<std::shared_ptr<AbilityFactory>> tempQue = this->abilities;

    file.write(this->queueSize());
    file.write("\n");
    while(!tempQue.empty()){
        std::string factName = tempQue.front()->getName();
        file.write(factName);
        file.write("\n");
        tempQue.pop();
    }
}

void AbilityManager::deserialize(FileWrapper& file){
    this->abilities = std::queue<std::shared_ptr<AbilityFactory>>();

    int queue_length;
    file.read(queue_length);

    for (int i = 0; i < queue_length; ++i) {
        std::string factoryName;
        file.read(factoryName);
        for (int j = 0; j < this->abilityProduction.getAbilitiesQuantity(); ++j) {
            if (factoryName == this->abilityProduction.getFactory(j)->getName()){
                abilities.push(this->abilityProduction.getFactory(j));
            }
        }
    }
}