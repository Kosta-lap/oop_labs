#ifndef OOP_FIELD_CELL_H
#define OOP_FIELD_CELL_H
#include "../core/ship.h"

enum class CellState{Unknown, Empty, Ship};

struct FieldCell{
    CellState cell_state;
    Ship* ship_pointer;
    int segment_index;
};


#endif