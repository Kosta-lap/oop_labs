#include "game_controller.h"
#include "../IOlogic/commands.h"
#include "game_save_loader.h"


template <typename InputType, typename OutputType, typename PaintType>
GameController<InputType,OutputType,PaintType>::GameController(Game& gamePointer):game(gamePointer) {
    this->input = new InputType();
    this->output = new OutputType();
    this->paint = new PaintType();
}

template <typename InputType, typename OutputType, typename PaintType>
GameController<InputType,OutputType,PaintType>::~GameController(){
    delete input;
    delete output;
    delete paint;
}

template <typename InputType, typename OutputType, typename PaintType>
bool GameController<InputType, OutputType, PaintType>::initialization() {
    input->loadCommands("../attribs");

    output->display("Welcome to the sea battle!\n");
    output->printWelcomeCommands(input->getCommands());

    bool correct_input = false;
    while(!correct_input){
        InputCommand choice = input->readCommand();

        if(choice == InputCommand::Input){
            output->clear();

            output->display("To continue, select the coordinates for the ships\n");
            output->display("Coordinates are entered in this way: X (0-9) Y (0-9) orientation (0 - horizontal, 1 - vertical)\n");

            ShipManager& player_sm = game.getGameState().getPlayerShipManager();
            for (int i = 0; i < player_sm.getShipCount(); ++i) {
                Point point = {0, 0};
                int orientation = 0;

                Ship* ship = player_sm.getShip(i);
                bool placed = false;

                while(!placed){
                    try{
                        output->display("Enter the coordinates for the ship of length " + std::to_string(ship->getShipLength()) + ": ");

                        point = input->getCords();
                        orientation = input->getValidInput();

                        placed = game.getGameState().placePlayerShip(point, orientation, i);

                    }catch (const std::invalid_argument& e) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        output->display(e.what());
                        output->display("\n");
                    }
                }
            }
            game.getGameState().placeEnemyShips();
            correct_input = true;
        }

        if(choice == InputCommand::Load){
            GameSaveLoader saverLoader = GameSaveLoader("../game.txt");
            try{
                saverLoader.load(game);
            }catch (const std::invalid_argument& e){
                output->display(e.what());
                output->display(" Try to creat the new one\n");
                continue;
            }
            correct_input = true;
        }

        if(choice == InputCommand::Exit){
            return false;
        }

        if(!correct_input){
            output->display("Unknown command!\n");
        }

    }
    return true;
}

template <typename InputType, typename OutputType, typename PaintType>
void GameController<InputType, OutputType, PaintType>::play() {
    bool is_end = this->initialization();

    if(!is_end){
        return;
    }

    bool game_running = true;
    output->display("Everything was successful!\n");
    while (game_running){
        output->clear();
        output->display("Current round: " + std::to_string(game.getCurrentRound()) + "\n");
        paint->printBattleField(game.getGameState().getPlayerField(), game.getGameState().getEnemyField());

        output->display("\nAvailable abilities: " + std::to_string(game.getGameState().getAbilitiesCount()) + "\n");
        output->display("The first available ability: " + game.getGameState().getLastAbilityName() + "\n");
        output->printGameCommands(input->getCommands());
        InputCommand choice = input->readCommand();

        switch (choice) {
            case InputCommand::Ability:{
                AbilityUsageInfo info;

                if(game.getGameState().getLastAbilityName() == "Scanner"){info.needsCoordinates = true;}
                if(info.needsCoordinates){
                    output->display("Choose the coords to scanner: ");
                    info.coordinates = input->getCords();
                }

                game.usePlayerAbility(info);

                if (info.errorOccurred) {
                    output->display("Error using ability.\n");
                } else if (info.noAbilities) {
                    output->display("No abilities available.\n");
                }else if (info.isDoubleDamage) {
                    output->display("Double damage activated!\n");
                } else if (info.randomShotPerformed) {
                    output->display("Random shot performed!\n");
                }

                if (info.resultOfScanner) {
                    output->display("Ship has been detected on this cords!\n");
                }else if(info.needsCoordinates && !info.resultOfScanner){
                    output->display("Ship hasn`t been detected on this cords!\n");
                }
            }
            case InputCommand::Attack:{
                bool correct_shoot = false;
                output->display("Choose the coords to attack: ");

                while(!correct_shoot){
                    Point cords_for_shoot = input->getCords();
                    try{
                        game.playerShoot(cords_for_shoot);
                        correct_shoot = true;
                    }catch (const std::invalid_argument& e) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        output->display(e.what());
                        output->display("\n");
                    }
                }

                if(game.isPlayerWon()){
                    output->clear();
                    output->display("Congratulations! You won!!!!!\n");
                    output->display("Creating new round, wait pls....\n");
                    game.newRound();
                    output->wait();

                    continue;
                }

                break;
            }
            case InputCommand::Save:{
                GameSaveLoader saverLoader("../game.txt");
                saverLoader.save(game);

                output->clear();
                output->display("Game has been saved!\n");
                continue;
            }
            case InputCommand::Load:{
                GameSaveLoader saverLoader = GameSaveLoader("../game.txt");
                try{
                    saverLoader.load(game);
                }catch (const std::invalid_argument& e){
                    output->clear();
                    output->display(e.what());
                    output->display("\n");
                    output->display("Can't load the save :(\n");
                    continue;
                }

                output->clear();
                output->display("Game has been loaded!\n");
                continue;
            }
            case InputCommand::Exit:{
                output->clear();
                output->display("Thank you for playing!\n");
                output->wait();

                game_running = false;
                continue;
            }
            default:{
                output->display("There is no such command :(\n");
                output->wait();

                continue;
            }
        }
        game.enemyTurn();
        if(game.isPlayerLose()){
            output->clear();
            output->display("You lose(\n");
            output->display("You lasted for " + std::to_string(game.getCurrentRound() - 1) + " round!\n");
            output->display("They'll take you next time) \n");
            output->wait();

            game_running = false;
            continue;
        }
    }

}

template class GameController<CliInput, CliOutput, Printer>;