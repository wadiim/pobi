#ifndef FIRST_NAME_PREDICATE_H
#define FIRST_NAME_PREDICATE_H

#include "typedefs.h"

#include <string>
#include <boost/regex.hpp>

class FirstNamePredicate
{
        boost::regex pattern;
public:
        explicit FirstNamePredicate(const std::string &pattern);

        bool operator()(const ClientPtr &client) const;
};

#endif // FIRST_NAME_PREDICATE_H
