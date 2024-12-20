#ifndef OOP_CLI_OUTPUT_H
#define OOP_CLI_OUTPUT_H

#include "iostream"
#include "map"
#include "commands.h"
#include "Windows.h"

class CliOutput {
    private:
        std::map<InputCommand, std::string> commands_to_string;

    public:
        CliOutput();

        void display(std::string_view message);
        void printCommand(int symbol, InputCommand command);
        void printWelcomeCommands(std::map<int, InputCommand> commands_map);
        void printGameCommands(std::map<int, InputCommand> commands_map);

        void clear();
        void wait();
};


#endif