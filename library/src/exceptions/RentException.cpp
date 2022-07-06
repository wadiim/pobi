#include "exceptions/RentException.h"

RentException::RentException(const std::string &message)
        : logic_error{message}
{
}