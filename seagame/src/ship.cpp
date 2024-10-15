#include "../ship.h"
#include "stdexcept"
#include "iostream"

Ship::Ship(int length){
    if(length < 1 || length > 4) {throw std::invalid_argument("Wrong length!");}

    this->length = length;
    coords = {0, 0};
    isHorizontal = true;

    for (int i = 0; i < length; i++) {
        segments.push_back(SegmentState::Intact);
    }
}

int Ship::getShipLength() {
    return length;
}

bool Ship::getIsHorizontal() {
    return isHorizontal;
}

Point Ship::getCoordinates(){
    return coords;
}

void Ship::setShipSpec(Point new_coords, bool is_horizontal){
   this->coords = new_coords;
   this->isHorizontal = is_horizontal;
}

bool Ship:: isDestroyed(){
    for (auto segment: segments) {
        if(segment != SegmentState::Damaged){
            return false;
        }
    }
    return true;
}

void Ship::hitSegment(int index) {
    if(index >= 0 && index < length){
        switch(segments[index])
        {
            case SegmentState::Intact:
                segments[index] = SegmentState::Damaged;
                break;
            case SegmentState::Damaged:
                segments[index] = SegmentState::Destroyed;
                break;
        }
    }else{
        throw std::invalid_argument("Wrong length!");
    }
}

SegmentState Ship::getSegmentState(int index) {
    if(index >= 0 && index < length){
        return segments[index];
    }else{
        throw std::invalid_argument("Wrong length!");
    }
}

void Ship::printShipSegments(){
    for (int i = 0; i < getShipLength(); ++i) {
        std::cout << "Segment " << i << " state: " << (getSegmentState(i) == SegmentState::Intact ? "Intact" : getSegmentState(i) == SegmentState::Damaged ? "Damaged" : "Destroyed") << "\n";
    }
}