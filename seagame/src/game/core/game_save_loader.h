#ifndef OOP_GAME_SAVE_LOADER_H
#define OOP_GAME_SAVE_LOADER_H

#include "game.h"
#include "game_state.h"
#include "../../common/FileWrapper.h"

class GameSaveLoader {
    private:
        std::string filename;
    public:
        GameSaveLoader(std::string_view filename);

        void save(const GameState& game_state, int round);
        void load(GameState& game_state, int& round);

        void save(Game& game);
        void load(Game& game);
        int getSum();
};

#endif
