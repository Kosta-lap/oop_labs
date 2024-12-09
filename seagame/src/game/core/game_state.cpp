#include "game_state.h"
#include "../../abilities/core/add_new_ability.h"
#include "../../abilities/errors/ability_extract_error.h"

GameState::GameState() {
    this->player_gf = new GameField(10, 10);
    this->enemy_gf = new GameField(10, 10);
    this->player_sm = new ShipManager(4, {1, 2, 3, 4});
    this->enemy_sm = new ShipManager(4, {1, 2, 3, 4});
    this->player_am = new AbilityManager();

    // При уничтожении кораблей врага, + 1 способность
    std::shared_ptr<AddNewAbility> reaction = std::make_shared<AddNewAbility>(*player_am);
    enemy_gf->setCommand(reaction);
    // При уничтожении кораблей пользователя ничего не происходит
    player_gf->setCommand(nullptr);
}

GameState::~GameState() {
    delete player_gf;
    delete enemy_gf;
    delete player_sm;
    delete enemy_sm;
    delete player_am;
}

bool GameState::placePlayerShip(Point point, int orientation, int index){
    Ship* ship = player_sm->getShip(index);

    try{
        player_gf->placeShip(ship, point, orientation);
        this->player_cords.push_back(point);
        this->player_orient.push_back(orientation);

        return true;
    }catch(PlaceError &err){
        std::cout << err.what() << "\n";
        return false;
    }
}

void GameState::placeEnemyShips(){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis_width(0, this->enemy_gf->getFieldWidth() - 1);
    std::uniform_int_distribution<> dis_height(0, this->enemy_gf->getFieldHeight() - 1);
    std::uniform_int_distribution<> dis_orientation(0, 1);

    int index = 0;
    while (index < enemy_sm->getShipCount()){
        int x = dis_width(gen);
        int y = dis_height(gen);
        int orientation = dis_orientation(gen);
        Ship* current_ship = enemy_sm->getShip(index);


        try{
            enemy_gf->placeShip(current_ship, {x, y}, orientation);
            this->enemy_cords.push_back({x, y});
            this->enemy_orient.push_back(orientation);
        }catch(PlaceError &err){
            continue;
        }

        index++;
    }
}

void GameState::useAbility(bool& is_double_damage) {
    try{
        std::shared_ptr<AbilityFactory> ab = player_am->extractAbility();
            if(ab->getName() == "Scanner"){
                bool flag = false;
                Point point = {0, 0};
                bool valid_input = false;
                while (!valid_input) {
                    std::cout << "Choose the coords to scanner: ";
                    try {
                        std::cin >> point.x >> point.y;
                        if (std::cin.fail()) {
                            throw std::invalid_argument("Invalid input. Please enter a number.");
                        } else {
                            enemy_gf->setAbility(ab->create(point, [&flag](bool is_there_ship){flag = is_there_ship;}));
                            valid_input = true;
                        }
                    } catch (const std::invalid_argument& e) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << e.what() << "\n";
                    }
                }

                if(flag){
                    std::cout << "Ship is detected" << "\n";
                }else{
                    std::cout << "Ship is not detected" << "\n";
                }
                std::cout << "\n";
            }else if(ab->getName() == "DoubleDamage"){
                enemy_gf->setAbility(ab->create({},[&is_double_damage](bool is_dd){is_double_damage = is_dd;}));
            }else if(ab->getName() == "RandomShot"){
                enemy_gf->setAbility(ab->create());
                std::cout << "Our artillery has successfully covered them!" << "\n";
            }
    }catch(AbilityExtractError(& err)){
        std::cerr<<"Error: " << err.what() << "\n";
    }
}

int GameState::getAbilitiesCount(){
    return player_am->queueSize();
}

void GameState::printBattleField() {
    std::cout << "  Player Field\t\t\t  Enemy Field\n";
    std::cout << "  ";
    for (int j = 0; j < player_gf->getFieldWidth(); ++j) {
        std::cout << j << " ";
    }
    std::cout << "\t\t  ";
    for (int j = 0; j < enemy_gf->getFieldWidth(); ++j) {
        std::cout << j << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < player_gf->getFieldHeight(); ++i) {
        std::cout << i << " ";
        for (int j = 0; j < player_gf->getFieldWidth(); ++j) {
            FieldCell* state = player_gf->getCellInfo({j, i});

            if (state->cell_state == CellState::Unknown) {
                if(state->ship_pointer != nullptr){
                    std::cout << "■ ";
                    continue;
                }
                std::cout << "□ ";
            }else if(state->cell_state == CellState::Ship){
                if(state->ship_pointer->getSegment(state->segment_index) == SegmentState::Damaged){
                    std::cout << "◧ ";
                }else if(state->ship_pointer->getSegment(state->segment_index) == SegmentState::Destroyed){
                    std::cout << "▧ ";
                }
            }else if (state->cell_state == CellState::Empty) {
                std::cout << "● ";
            }
        }
        std::cout << "\t\t" << i << " ";
        for (int j = 0; j < enemy_gf->getFieldWidth(); ++j) {
            FieldCell* state = enemy_gf->getCellInfo({j, i});
            if (state->cell_state == CellState::Unknown) {
                std::cout << "□ ";
            } else if (state->cell_state == CellState::Empty) {
                std::cout << "● ";
            } else if (state->cell_state == CellState::Ship) {
                if(state->ship_pointer->getSegment(state->segment_index) == SegmentState::Damaged){
                    std::cout << "◧ ";
                }else if(state->ship_pointer->getSegment(state->segment_index) == SegmentState::Destroyed){
                    std::cout << "▧ ";
                }
            }
        }
        std::cout << "\n";
    }
}

void GameState::resetEnemy() {
    const int old_width = enemy_gf->getFieldWidth();
    const int old_height = enemy_gf->getFieldHeight();

    GameField* new_enemy_gf = new GameField(old_width, old_height);
    ShipManager* new_enemy_sm = new ShipManager(4, {1, 2, 3, 4});

    new_enemy_gf->setCommand(enemy_gf->getCommand());

    delete enemy_gf;
    delete enemy_sm;
    enemy_gf = new_enemy_gf;
    enemy_sm = new_enemy_sm;

    this->placeEnemyShips();
}

GameField &GameState::getPlayerField() {
    return *player_gf;
}

GameField &GameState::getEnemyField(){
    return *enemy_gf;
}

ShipManager &GameState::getPlayerShipManager() {
    return *player_sm;
}

ShipManager &GameState::getEnemyShipManager() {
    return *enemy_sm;
}

std::string GameState::getLastAbilityName() {
    return player_am->getLastName();
}

FileWrapper& operator<<(FileWrapper& file, const GameState& game_state) {
    game_state.player_sm->serialize(file);
    for (int i = 0; i < game_state.player_sm->getShipCount(); ++i) {
        file.write(game_state.player_cords[i].x);
        file.write(" ");
        file.write(game_state.player_cords[i].y);
        file.write(" ");
        file.write(game_state.player_orient[i]);
        file.write("\n");
    }
    game_state.player_gf->serialize(file);
    game_state.player_am->serialize(file);

    game_state.enemy_sm->serialize(file);
    for (int i = 0; i < game_state.enemy_sm->getShipCount(); ++i) {
        file.write(game_state.enemy_cords[i].x);
        file.write(" ");
        file.write(game_state.enemy_cords[i].y);
        file.write(" ");
        file.write(game_state.enemy_orient[i]);
        file.write("\n");
    }
    game_state.enemy_gf->serialize(file);
    return file;
}

FileWrapper &operator>>(FileWrapper &file, GameState &game_state) {
    //Десериализация менджера кораблей игрока
    game_state.player_sm->deserialize(file);
    game_state.player_cords.clear();
    game_state.player_orient.clear();
    for (int i = 0; i < game_state.player_sm->getShipCount(); ++i) {
        Point point;
        int orientation;

        file.read(point.x);
        file.read(point.y);
        file.read(orientation);

        game_state.player_cords.push_back(point);
        game_state.player_orient.push_back(orientation);
    }
    //Десериализация поля игрока
    game_state.player_gf->deserialize(file);
    for (int i = 0; i < game_state.player_sm->getShipCount(); ++i) {
        Ship* ship = game_state.player_sm->getShip(i);
        game_state.player_gf->placeShip(ship, game_state.player_cords[i], game_state.player_orient[i]);
    }
    //Десериализация способностей
    game_state.player_am->deserialize(file);


    game_state.enemy_sm->deserialize(file);
    game_state.enemy_cords.clear();
    game_state.enemy_orient.clear();
    for (int i = 0; i < game_state.enemy_sm->getShipCount(); ++i) {
        Point point;
        int orientation;

        file.read(point.x);
        file.read(point.y);
        file.read(orientation);

        game_state.enemy_cords.push_back(point);
        game_state.enemy_orient.push_back(orientation);
    }
    //Десериализация поля игрока
    game_state.enemy_gf->deserialize(file);
    for (int i = 0; i < game_state.enemy_sm->getShipCount(); ++i) {
        Ship* ship = game_state.enemy_sm->getShip(i);
        game_state.enemy_gf->placeShip(ship, game_state.enemy_cords[i], game_state.enemy_orient[i]);
    }
    return file;
}
