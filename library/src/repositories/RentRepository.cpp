#include "repositories/RentRepository.h"
#include "model/Rent.h"

RentPtr RentRepository::getRent(size_t index) const
{
	return get(index);
}

void RentRepository::addRent(RentPtr rent)
{
	add(std::move(rent));
}

void RentRepository::removeRent(RentPtr rent)
{
	remove(std::move(rent));
}
