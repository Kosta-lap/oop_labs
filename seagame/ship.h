#ifndef OOP_SHIP_H
#define OOP_SHIP_H

#include "vector"
#include "point.h"

enum class SegmentState {Intact, Damaged, Destroyed};

class Ship {
    private:
        int length;
        std::vector<SegmentState> segments;

    public:
        explicit Ship(int length);

        int getShipLength();
        bool isDestroyed();

        void hitSegment(int index);
        SegmentState getSegment(int index);
        void printShipSegments();
};


#endif
