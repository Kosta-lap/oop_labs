#include "game.h"
#include "Windows.h"
#include "game_save_loader.h"

Game::Game() {
    this->is_player_turn = true;
    this->is_double_damage = false;
    this->round = 1;
}

void Game::start() {
    int choice;

    std::cout << "Welcome to the sea battle!" << "\n";
    std::cout << "Choose the option: 0 - Start new game; 1 - Load game" << '\n';

    choice = getValidInput();

    system("cls");

    if (choice){
        GameSaveLoader saverLoader = GameSaveLoader("../game.txt");
        try{
            saverLoader.load(game_state, this->round);
        }catch (const std::invalid_argument& e){
            std::cout << e.what() << "\n";
            std::cout << "Starting a new game instead.\n";
            choice = 0;
        }
    }

    if (choice == 0){
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
            try{
                std::cout << "Enter the coordinates for the ship of length " << ship->getShipLength() << ": ";
                std::cin >> point.x >> point.y >> orientation;

                if (std::cin.fail()) {
                    throw std::invalid_argument("Invalid input. Please enter numbers.");
                }
                placed = game_state.placePlayerShip(point, orientation, i);

            }catch (const std::invalid_argument& e) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << e.what() << "\n";
            }
        }
    }
    system("cls");
}

void Game::play() {
    bool game_running = true;
    std::cout << "Everything was successful!\n";

    while (game_running){
        if(is_player_turn){
            int choice;
            std::cout << "Current round: " << this->round << "\n";
            game_state.printBattleField();
            std::cout << "\n";
            std::cout << "Available abilities: " << game_state.getAbilitiesCount() << "\n";
            std::cout << "The first available ability: " << game_state.getLastAbilityName() << "\n";
            std::cout << "Choose the action: 0 - Attack the enemy; 1 - Use ability; 2 - Save game; 3 - Load game; 4 - Exit" << '\n';

            choice = getValidInput();

            if(choice == 2){
                GameSaveLoader saverLoader("../game.txt");
                saverLoader.save(game_state, this->round);

                system("cls");
                std::cout << "Game has been saved!" << "\n";
                continue;
            }else if(choice == 3){
                GameSaveLoader saverLoader = GameSaveLoader("../game.txt");
                try{
                    saverLoader.load(game_state, this->round);
                }catch (const std::invalid_argument& e){
                    system("cls");
                    std::cout << e.what() << "\n";
                    std::cout << "Can't load the save :(\n";
                    continue;
                }

                system("cls");
                std::cout << "Game has been loaded!" << "\n";
                continue;
            }else if(choice == 4){
                system("cls");
                std::cout << "Thank you for playing!" << "\n";
                Sleep(2000);
                game_running = false;

                continue;
            }else if(choice > 4 || choice < 0){
                std::cout << "There is no such command :(" << "\n";
                Sleep(500);
                system("cls");
                continue;
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
                game_running = false;
                continue;
            }
            is_player_turn = true;
        }
        system("cls");
    }
}

void Game::playerTurn(int choice){
    bool valid_attack = false;
    Point point = {0, 0};
    if(choice == 1){
        game_state.useAbility(is_double_damage);
    }

    while(!valid_attack){
        std::cout << "Choose the coords to attack: ";
        point.x = getValidInput();
        point.y = getValidInput();
        try{
            game_state.getEnemyField().attackField(point, this->is_double_damage);
            valid_attack = true;
        } catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << e.what() << "\n";
        }
    }
}

void Game::enemyTurn(){
    bool fake_dd = false;
    bool valid_attack = false;
    GameField& player_gf =  game_state.getPlayerField();

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

void Game::newRound() {
    this->round++;
    std::cout << "New round started\n";

    game_state.resetEnemy();
}

int Game::getValidInput() {
    int num;
    bool valid_input = false;
    while (!valid_input) {
        try {
            std::cin >> num;
            if (std::cin.fail()) {
                throw std::invalid_argument("Invalid input. Please enter a number.");
            }
            valid_input = true;
        } catch (const std::invalid_argument& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << e.what() << "\n";
        }
    }
    return num;
}