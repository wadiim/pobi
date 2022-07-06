#ifndef VEHICLE_EXCEPTION_H
#define VEHICLE_EXCEPTION_H

#include <stdexcept>
#include <string>

class VehicleException : public std::logic_error
{
public:
        explicit VehicleException(const std::string &message);
};

#endif // VEHICLE_EXCEPTION_H