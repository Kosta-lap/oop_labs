#include "game_save_loader.h"

GameSaveLoader::GameSaveLoader(const std::string& filename) : filename(filename) {}

void GameSaveLoader::save(const GameState &game_state, int round) {
    FileWrapper file(filename, std::ios::out);
    file << game_state;
    file.write(round);
}

void GameSaveLoader::load(GameState& game_state, int& round) {
    FileWrapper file(filename, std::ios::in);
    file >> game_state;
    file.read(round);
}