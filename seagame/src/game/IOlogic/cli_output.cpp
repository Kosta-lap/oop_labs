#include "cli_output.h"

CliOutput::CliOutput() {
    commands_to_string[InputCommand::Attack] = "Attack the enemy";
    commands_to_string[InputCommand::Ability] = "Use ability";
    commands_to_string[InputCommand::Save] = "Save game";
    commands_to_string[InputCommand::Load] = "Load game";
    commands_to_string[InputCommand::Exit] = "Exit game";
    commands_to_string[InputCommand::Input] = "Start new game";
}

void CliOutput::printWelcomeCommands(std::map<int, InputCommand> commands_map){
    this->display("Choose the option: ");
    for (const auto& pair: commands_map){
       if(pair.second == InputCommand::Input || pair.second == InputCommand::Load || pair.second == InputCommand::Exit){
           this->printCommand(pair.first, pair.second);
       }
    }
    this->display("\n");
}

void CliOutput::printGameCommands(std::map<int, InputCommand> commands_map){
    this->display("Choose the option: ");
    for (const auto& pair: commands_map){
        if(pair.second != InputCommand::Input){
            this->printCommand(pair.first, pair.second);
        }
    }
    this->display("\n");
}

void CliOutput::printCommand(int symbol, InputCommand command){
    std::cout << symbol << " - " << commands_to_string[command] << "; ";
}

void CliOutput::display(std::string_view message) {
    std::cout << message;
}

void CliOutput::clear() {
    system("cls");
}

void CliOutput::wait() {
    Sleep(1500);
}
