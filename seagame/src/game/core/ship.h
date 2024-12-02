#ifndef OOP_SHIP_H
#define OOP_SHIP_H

#include "vector"
#include "../utils/point.h"

enum class SegmentState {Intact, Damaged, Destroyed};

class Ship {
    private:
        int length;
        std::vector<SegmentState> segments;

    public:
        explicit Ship(int length);

        int getShipLength();
        bool isDestroyed();

        void hitSegment(int index, bool is_double_damage);
        void setSegment(int index, SegmentState state);

        SegmentState getSegment(int index);
};


#endif
