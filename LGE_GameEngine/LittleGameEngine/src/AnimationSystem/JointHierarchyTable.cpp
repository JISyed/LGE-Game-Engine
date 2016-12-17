#include "JointHierarchyTable.h"
#include <cassert>

namespace lge
{
	JointHierarchyTable::JointHierarchyTable(const unsigned int tableSize, const unsigned int* const hierarchyData) :
		size(tableSize),
		parentIndices(hierarchyData)
	{
		assert(hierarchyData != nullptr);
	}

	JointHierarchyTable::~JointHierarchyTable()
	{
		delete[] this->parentIndices;
	}


	// Get the size of this table
	const unsigned int JointHierarchyTable::GetSize() const
	{
		return this->size;
	}

	// Get the parent index of the joint of the given index
	const unsigned int JointHierarchyTable::GetParentIndexOf(const unsigned int childIndex) const
	{
		assert(childIndex < this->size);
		return this->parentIndices[childIndex];
	}

	// Same as GetParentIndexOf() (Get the parent index of the joint of the given index)
	const unsigned int JointHierarchyTable::operator[](const unsigned int childIndex) const
	{
		return this->GetParentIndexOf(childIndex);
	}




}