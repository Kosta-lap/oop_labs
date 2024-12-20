#ifndef OOP_CLI_INPUT_H
#define OOP_CLI_INPUT_H

#include "iostream"
#include "map"
#include "set"
#include "vector"
#include "commands.h"
#include "../utils/point.h"
#include "../../common/FileWrapper.h"

class CliInput {
    private:
        std::map<int, InputCommand> commands_map;
        std::map<std::string, InputCommand> string_map;

        void fillDefault();
    public:
        CliInput();
        void loadCommands(std::string filename);

        InputCommand readCommand();
        std::map<int, InputCommand> getCommands();

        Point getCords();
        int getValidInput();
};


#endif
