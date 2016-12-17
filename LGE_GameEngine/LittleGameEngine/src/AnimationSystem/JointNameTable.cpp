#include "JointNameTable.h"
#include <cassert>

namespace lge
{
	JointNameTable::JointNameTable(const unsigned int tableSize, const CString* const nameArray) :
		size(tableSize),
		names(nameArray)
	{
		assert(nameArray != nullptr);
	}

	JointNameTable::~JointNameTable()
	{
		delete[] this->names;
	}




	// Get the size of this table
	const unsigned int JointNameTable::GetSize() const
	{
		return this->size;
	}

	// Get the name of the joint of the given index
	const CString& JointNameTable::GetNameOf(const unsigned int jointIndex) const
	{
		assert(jointIndex < this->size);
		return this->names[jointIndex];
	}

	// Same as GetNameOf() (Get the name of the joint of the given index)
	const CString& JointNameTable::operator[](const unsigned int jointIndex) const
	{
		return this->GetNameOf(jointIndex);
	}


}