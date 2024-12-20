#include "ship.h"
#include "stdexcept"
#include "iostream"

Ship::Ship(int length){
    if(length < 1 || length > 4) {throw std::invalid_argument("Wrong length!");}

    this->length = length;

    for (int i = 0; i < length; i++) {
        segments.push_back(SegmentState::Intact);
    }
}

int Ship::getShipLength() {
    return length;
}


bool Ship:: isDestroyed(){
    int count = 0;
    for (auto segment: segments) {
        if(segment == SegmentState::Destroyed){
            count++;
        }
    }
    if (count == this->length){
        return true;
    }else{
        return false;
    }
}

void Ship::hitSegment(int index, bool is_double_damage) {
    if(index >= 0 && index < length){
        if(is_double_damage) {
            segments[index] = SegmentState::Destroyed;
            return;
        }
        switch(segments[index])
        {
            case SegmentState::Intact:
                segments[index] = SegmentState::Damaged;
                break;
            case SegmentState::Damaged:
                segments[index] = SegmentState::Destroyed;
                break;
            case SegmentState::Destroyed:
                break;
        }
    }else{
        throw std::invalid_argument("Wrong length!");
    }
}

SegmentState Ship::getSegment(int index) {
    if(index >= 0 && index < length){
        return segments[index];
    }else{
        throw std::invalid_argument("Wrong length!");
    }
}

void Ship::setSegment(int index, SegmentState state){
    segments[index] = state;
}