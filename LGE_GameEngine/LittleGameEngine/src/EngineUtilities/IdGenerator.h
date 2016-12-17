#ifndef LGE_ID_GEN_H
#define LGE_ID_GEN_H

namespace lge
{
	// Stand-alone generator for IDs. Multiple instances can exist. First value is 1
	class IdGenerator
	{
	public:

		//
		// Big Four
		//

		IdGenerator();
		IdGenerator(const unsigned int startingValue);
		~IdGenerator();
		IdGenerator& operator=(const IdGenerator& rhs);


		//
		// Methods
		//

		// Generate a new ID and return it. Guranateed to be unique up to about 4 billion
		const unsigned int MakeNewId();


	private:

		//
		// Data
		//

		unsigned int currentId;



		//
		// Deleted Methods
		//

		// No move ctor
		IdGenerator(IdGenerator&& other) = delete;

		// No move assignment
		IdGenerator& operator=(IdGenerator&& other) = delete;
	};
	
}

#endif