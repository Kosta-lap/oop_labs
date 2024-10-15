#ifndef OOP_SHIP_H
#define OOP_SHIP_H

#include "vector"
#include "point.h"

enum class SegmentState {Intact, Damaged, Destroyed};

class Ship {
    private:
        int length;
        bool isHorizontal;

        Point coords;
        std::vector<SegmentState> segments;

    public:
        explicit Ship(int length);

        int getShipLength();
        bool getIsHorizontal();
        Point getCoordinates();

        void setShipSpec(Point new_coords, bool is_horizontal);

        bool isDestroyed();

        void hitSegment(int index);
        SegmentState getSegmentState(int index);
        void printShipSegments();
};


#endif
