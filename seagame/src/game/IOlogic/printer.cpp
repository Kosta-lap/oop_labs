#include "printer.h"

void Printer::printBattleField(GameField &player_gf, GameField &enemy_gf) {
    std::cout << "  Player Field\t\t\t  Enemy Field\n";
    std::cout << "  ";
    for (int j = 0; j < player_gf.getFieldWidth(); ++j) {
        std::cout << j << " ";
    }
    std::cout << "\t\t  ";
    for (int j = 0; j < enemy_gf.getFieldWidth(); ++j) {
        std::cout << j << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < player_gf.getFieldHeight(); ++i) {
        std::cout << i << " ";
        for (int j = 0; j < player_gf.getFieldWidth(); ++j) {
            FieldCell* state = player_gf.getCellInfo({j, i});

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
        for (int j = 0; j < enemy_gf.getFieldWidth(); ++j) {
            FieldCell* state = enemy_gf.getCellInfo({j, i});
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
