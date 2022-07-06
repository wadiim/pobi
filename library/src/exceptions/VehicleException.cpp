#include "exceptions/VehicleException.h"

VehicleException::VehicleException(const std::string &message)
        : std::logic_error{message}
{
}