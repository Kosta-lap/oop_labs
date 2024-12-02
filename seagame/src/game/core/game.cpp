#include "game.h"
#include "Windows.h"
#include "game_save_loader.h"

Game::Game() {
    this->is_player_turn = true;
    this->is_double_damage = false;
    this->round = 1;
}

void Game::start() {
    int choice = 0;

    std::cout << "Welcome to the sea battle!" << "\n";
    std::cout << "Choose the option: 0 - Start new game; 1 - Load game" << '\n';

    std::cin >> choice;
    system("cls");

    if (choice){
        GameSaveLoader saverLoader("../game.txt");
        saverLoader.load(game_state, this->round);
    }else{
        this->inputPlayerData();
        this->game_state.placeEnemyShips();
    }

    this->play();
}

void Game::inputPlayerData() {
    std::cout << "To continue, select the coordinates for the ships\n";
    std::cout << "Coordinates are entered in this way: X (0-9) Y (0-9) orientation (0 - horizontal, 1 - vertical)\n";

    ShipManager& player_sm = game_state.getPlayerShipManager();
    for (int i = 0; i < player_sm.getShipCount(); ++i) {
        Point point = {0, 0};
        int orientation = 0;

        Ship* ship = player_sm.getShip(i);
        bool placed = false;

        while(!placed){
            std::cout << "Enter the coordinates for the ship of length " << ship->getShipLength() << ": ";
            std::cin >> point.x >> point.y >> orientation;

            placed = game_state.placePlayerShip(point, orientation, i);
        }
    }
    system("cls");
}

void Game::play() {
    std::cout << "Everything was successful!\n";

    while (true){
        if(is_player_turn){
            int choice = 0;
            std::cout << "Current round: " << this->round << "\n";
            game_state.printBattleField();
            std::cout << "\n";
            std::cout << "Available abilities: " << game_state.getAbilitiesCount() << "\n";
            std::cout << "The first available ability: " << game_state.getLastAbilityName() << "\n";
            std::cout << "Choose the action: 0 - Attack the enemy; 1 - Use ability; 2 - Save game and exit" << '\n';
            std::cin >> choice;
            if(choice == 2){
                GameSaveLoader saverLoader("../game.txt");
                saverLoader.save(game_state, this->round);
                return;
            }

            playerTurn(choice);
            if(game_state.getEnemyShipManager().allAreDestroyed()){
                system("cls");
                std::cout << "Congratulations! You won!!!!!\n";
                std::cout << "Creating new round, wait pls....\n";
                Sleep(2000);

                this->newRound();
                continue;
            }
            is_player_turn = false;
        }else{
            this->enemyTurn();
            if(game_state.getPlayerShipManager().allAreDestroyed()){
                system("cls");
                std::cout << "You lose(\n";
                std::cout << "You lasted for " << this->round - 1 << " round!\n";
                std::cout << "They'll take you next time) \n";
                Sleep(2000);
                return;
            }
            is_player_turn = true;
        }
        system("cls");
    }
}

void Game::playerTurn(int choice){
    Point point = {0, 0};
    if(choice == 1){
        game_state.useAbility(is_double_damage);
    }

    std::cout << "Choose the coords to attack: ";
    std::cin >> point.x >> point.y;
    game_state.getEnemyField().attackField(point, this->is_double_damage);
}

void Game::enemyTurn(){
    bool fake_dd = false;
    GameField& player_gf =  game_state.getPlayerField();

    while (true){
        Point point = {0, 0};

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis_width(0, player_gf.getFieldWidth() - 1);
        std::uniform_int_distribution<> dis_height(0, player_gf.getFieldHeight() - 1);
        point.x = dis_width(gen);
        point.y = dis_height(gen);

        if(player_gf.getSellState(point) != CellState::Empty){
            player_gf.attackField(point, fake_dd);
            break;
        }
    }
}

void Game::newRound() {
    this->round++;
    std::cout << "New round started\n";

    game_state.resetEnemy();
}

//void Game::load() {
//    std::string filename = "../game.txt";
//    FileWrapper file = FileWrapper(filename, std::ios::in);
//
//    game_state.deserialize(file);
//    file.read(this->round);
//}
//
//void Game::save() {
//    std::string filename = "../game.txt";
//    FileWrapper file = FileWrapper(filename, std::ios::out);
//
//    game_state.serialize(file);
//    file.write(this->round);
//}