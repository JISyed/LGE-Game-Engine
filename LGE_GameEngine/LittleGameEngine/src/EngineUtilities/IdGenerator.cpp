#include "IdGenerator.h"

namespace lge
{
	IdGenerator::IdGenerator() :
		currentId(0u)
	{
	}

	IdGenerator::IdGenerator(const unsigned int startingValue) :
		currentId(startingValue)
	{
	}

	IdGenerator::~IdGenerator()
	{
	}

	IdGenerator& IdGenerator::operator=(const IdGenerator& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		this->currentId = rhs.currentId;

		return *this;
	}

	const unsigned int IdGenerator::MakeNewId()
	{
		return ++(this->currentId);
	}
}