#include "game.h"
#include "Windows.h"
#include "game_save_loader.h"

Game::Game() {
    this->is_double_damage = false;
    this->round = 1;
}

void Game::enemyTurn(){
    bool fake_dd = false;
    bool valid_attack = false;
    GameField& player_gf = game_state.getPlayerField();

    while (!valid_attack){
        Point point = {0, 0};

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis_width(0, player_gf.getFieldWidth() - 1);
        std::uniform_int_distribution<> dis_height(0, player_gf.getFieldHeight() - 1);
        point.x = dis_width(gen);
        point.y = dis_height(gen);

        CellState cell_state = player_gf.getSellState(point);
        if(cell_state != CellState::Empty){
            if(cell_state == CellState::Ship){
                FieldCell* cell = player_gf.getCellInfo(point);
                if(cell->ship_pointer->getSegment(cell->segment_index) == SegmentState::Destroyed){
                    continue;
                }
            }
            player_gf.attackField(point, fake_dd);
            valid_attack = true;
        }
    }
}

void Game::usePlayerAbility(AbilityUsageInfo& info) {
    game_state.useAbility(is_double_damage, info);
}

bool Game::isPlayerLose() {
    return game_state.getPlayerShipManager().allAreDestroyed();
}

bool Game::isPlayerWon() {
    return game_state.getEnemyShipManager().allAreDestroyed();
}

void Game::newRound() {
    this->round++;
    game_state.resetEnemy();
}

void Game::playerShoot(Point cords) {
    game_state.getEnemyField().attackField(cords, this->is_double_damage);
}

int& Game::getCurrentRound() {
    return this->round;
}

GameState &Game::getGameState() {
    return game_state;
}
