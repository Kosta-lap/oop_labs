#include "game_save_loader.h"

GameSaveLoader::GameSaveLoader(std::string_view filename) : filename(filename) {}

void GameSaveLoader::save(const GameState &game_state, int round) {
    FileWrapper* file = new FileWrapper(filename, std::ios::out);
    *file << game_state;
    file->write(round);
    delete file;

    FileWrapper fileOfSum("../summary", std::ios::out);
    fileOfSum.write(getSum());
}

void GameSaveLoader::load(GameState& game_state, int& round) {
    int oldSum, fileSum;

    FileWrapper fileOfSum("../summary", std::ios::in);
    fileOfSum.read(oldSum);
    fileSum = getSum();

    if (oldSum != fileSum){
        throw std::invalid_argument("Data has been crashed!");
    }

    FileWrapper file(filename, std::ios::in);

    file >> game_state;
    file.read(round);
}

int GameSaveLoader::getSum(){
    FileWrapper file(filename, std::ios::in);
    int totalSum = 0;
    char ch;

    while(!file.isEof()) {
        file.read(ch);
        totalSum += static_cast<int>(ch);
    }

    return totalSum;
}