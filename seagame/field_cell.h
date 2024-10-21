#ifndef OOP_FIELD_CELL_H
#define OOP_FIELD_CELL_H


enum class SellState{Unknown, Empty, Ship};

struct FieldCell{
    SellState cell_state;
    Ship* ship_pointer;
    int segment_index;
};


#endif