#include "exceptions/ClientException.h"

ClientException::ClientException(const std::string &message)
        : logic_error{message}
{
}