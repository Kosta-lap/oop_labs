#ifndef OOP_GAME_SAVE_LOADER_H
#define OOP_GAME_SAVE_LOADER_H

#include "game_state.h"
#include "../../common/FileWrapper.h"

class GameSaveLoader {
    private:
        std::string filename;
    public:
        GameSaveLoader(const std::string& filename);

        void save(const GameState& game_state, int round);
        void load(GameState& game_state, int& round);
};


#endif
