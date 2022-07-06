#ifndef RENT_EXCEPTION_H
#define RENT_EXCEPTION_H

#include <stdexcept>
#include <string>

class RentException : public std::logic_error
{
public:
        explicit RentException(const std::string &message);
};

#endif // RENT_EXCEPTION_H