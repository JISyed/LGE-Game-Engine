#ifndef H_LGE_ANIMATION_JOINT_HIERARCHY_TABLE
#define H_LGE_ANIMATION_JOINT_HIERARCHY_TABLE

// Indicates that the joint doesn't have a parent
#define LGE_INVALID_JOINT_PARENT 0xFFFFFFFF

namespace lge
{
	// A look up table where the index is the child index and the data is the parent index
	class JointHierarchyTable
	{
	public:

		//
		// Ctor + Dtor
		//

		// Ctor with new table (size + data)
		JointHierarchyTable(const unsigned int tableSize, const unsigned int* const hierarchyData);
		
		// Dtor
		~JointHierarchyTable();


		//
		// Getters
		//

		// Get the size of this table
		const unsigned int GetSize() const;

		// Get the parent index of the joint of the given index
		const unsigned int GetParentIndexOf(const unsigned int childIndex) const;

		// Same as GetParentIndexOf() (Get the parent index of the joint of the given index)
		const unsigned int operator[](const unsigned int childIndex) const;



	private:

		//
		// Data
		//

		unsigned int size;					// The size of the table (usually the number of joints)
		const unsigned int* parentIndices;	// The index of the current entry's parent


		//
		// Deleted Methods
		//

		// No default ctor
		JointHierarchyTable() = delete;
		// No copy
		JointHierarchyTable(const JointHierarchyTable& other) = delete;
		// No copy
		JointHierarchyTable& operator=(const JointHierarchyTable& other) = delete;

	};

	
}

#endif