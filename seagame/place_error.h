#ifndef OOP_PLACE_ERROR_H
#define OOP_PLACE_ERROR_H

#include "stdexcept"

class PlaceError: public std::invalid_argument{
    public:
        PlaceError(const std::string &message): std::invalid_argument(message) {};
};

#endif