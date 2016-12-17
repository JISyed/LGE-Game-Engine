#ifndef H_LGE_ANIMATION_JOINT_NAME_TABLE
#define H_LGE_ANIMATION_JOINT_NAME_TABLE
#include "..\AbstractDataTypes\CString.h"

namespace lge
{
	// A look up table where the index is joint, and the data is its name
	class JointNameTable
	{
	public:

		//
		// Ctor + Dtor
		//

		// Ctor with new table (size + data)
		JointNameTable(const unsigned int tableSize, const CString* const nameArray);

		// Dtor
		~JointNameTable();




		//
		// Getters
		//

		// Get the size of this table
		const unsigned int GetSize() const;

		// Get the name of the joint of the given index
		const CString& GetNameOf(const unsigned int jointIndex) const;

		// Same as GetNameOf() (Get the name of the joint of the given index)
		const CString& operator[](const unsigned int jointIndex) const;


	private:

		//
		// Data
		//

		unsigned int size;		// The size of the table (usually the number of joints)
		const CString* names;	// The names of the joints (by index)



		//
		// Delete Methods
		//

		// No default ctor
		JointNameTable() = delete;
		// No copy
		JointNameTable(const JointNameTable& other) = delete;
		// No copy
		JointNameTable& operator=(const JointNameTable& other) = delete;
	};
}
#endif