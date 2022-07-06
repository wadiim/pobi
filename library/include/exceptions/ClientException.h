#ifndef CLIENT_EXCEPTION_H
#define CLIENT_EXCEPTION_H

#include <stdexcept>
#include <string>

class ClientException : public std::logic_error
{
public:
        explicit ClientException(const std::string &message);
};

#endif // CLIENT_EXCEPTION_H
