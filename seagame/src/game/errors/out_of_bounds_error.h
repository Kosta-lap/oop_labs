#ifndef OOP_OUT_OF_BOUNDS_ERROR_H
#define OOP_OUT_OF_BOUNDS_ERROR_H

#include "stdexcept"

class OutOfBoundsError: public std::invalid_argument{
    public:
        OutOfBoundsError(const std::string &message): std::invalid_argument(message) {};
};

#endif
