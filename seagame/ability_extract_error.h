#ifndef OOP_ABILITY_EXTRACT_ERROR_H
#define OOP_ABILITY_EXTRACT_ERROR_H

#include "stdexcept"

class AbilityExtractError: public std::runtime_error{
public:
    AbilityExtractError(const std::string &message): std::runtime_error(message) {};
};


#endif
