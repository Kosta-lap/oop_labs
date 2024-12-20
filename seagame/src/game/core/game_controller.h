#ifndef OOP_GAME_CONTROLLER_H
#define OOP_GAME_CONTROLLER_H

#include "game.h"
#include "../IOlogic/cli_input.h"
#include "../IOlogic/cli_output.h"
#include "../IOlogic/printer.h"


template <typename InputType, typename OutputType, typename PaintType>
class GameController {
    private:
        Game& game;

        InputType* input;
        OutputType* output;
        PaintType* paint;

    public:
        GameController(Game& gamePointer);
        ~GameController();

        bool initialization();
        void play();
};


#endif
