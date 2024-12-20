#include <limits>
#include "cli_input.h"

CliInput::CliInput() {
    string_map["Attack"] = InputCommand::Attack;
    string_map["Ability"] = InputCommand::Ability;
    string_map["Save"] = InputCommand::Save;
    string_map["Load"] = InputCommand::Load;
    string_map["Exit"] = InputCommand::Exit;
    string_map["Input"] = InputCommand::Input;
}

void CliInput::loadCommands(std::string filename) {
    try {
        FileWrapper commands_file(filename, std::ios::in);

        std::set<int> keys;
        std::set<std::string> commands;

        int key;
        std::string command;

        while (!commands_file.isEof()){
            commands_file.read(key);
            commands_file.read(command);

            if(keys.count(key) == 1){
                throw std::runtime_error("Duplicate key assignment: " + std::string(1, key + '0'));
            }

            if(commands.count(command) == 1){
                throw std::runtime_error("Duplicate command assignment: " + command);
            }

            if(string_map.count(command) == 0){
                throw std::runtime_error("Unknown command!");
            }

            commands_map[key] = string_map[command];
            keys.insert(key);
            commands.insert(command);
        }

        if (commands_map.size() < string_map.size()){
            throw std::runtime_error("Few commands!");
        }
    }catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';

        commands_map.clear();
        this->fillDefault();
    }

}

void CliInput::fillDefault() {
    std::vector<int> keys = {0, 1, 2, 3, 4, 5};
    std::vector<std::string> values = {"Input", "Attack", "Ability", "Save", "Load", "Exit"};

    for (int i = 0; i < keys.size(); i++) {
        commands_map[keys[i]] = string_map[values[i]];
    }
}

Point CliInput::getCords() {
    return {this->getValidInput(), this->getValidInput()};
}

int CliInput::getValidInput() {
    int num;
    bool valid_input = false;
    while (!valid_input) {
        try {
            std::cin >> num;
            if (std::cin.fail()) {
                throw std::invalid_argument("Invalid input. Please enter a number.");
            }
            valid_input = true;
        } catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << e.what() << "\n";
        }
    }
    return num;
}

InputCommand CliInput::readCommand() {
   int num = getValidInput();

   if(commands_map.count(num) == 0){
       return InputCommand::None;
   }
    return commands_map[num];
}

std::map<int, InputCommand> CliInput::getCommands(){
    return commands_map;
}