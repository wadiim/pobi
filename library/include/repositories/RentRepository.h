#ifndef RENT_REPOSITORY_H
#define RENT_REPOSITORY_H

#include "typedefs.h"
#include "repositories/Repository.h"

class RentRepository : public Repository<Rent>
{
public:
	RentRepository() = default;
	~RentRepository() override = default;

	RentPtr getRent(size_t index) const;
	void addRent(RentPtr rent);
	void removeRent(RentPtr rent);
};

#endif // RENT_REPOSITORY_H
