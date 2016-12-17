#ifndef LGE_GENERIC_LIST_H
#define LGE_GENERIC_LIST_H

#include "GenericListNode.h"
#include "GenericListIterator.h"

namespace lge
{
	// A collection of GenericListNodes that can only hold objects of type T (does not own).
	// The object MUST have the method "const unsigned int GetId() const".
	// Declare what classes will be held in this list by refering to the .cpp file.
	// This list was intended to be used by the resourse manager classes.
	template<typename T> class GenericList
	{
	public:

		//
		// Ctor / Dtor
		//

		GenericList();
		~GenericList();




		//
		// Methods
		//

		// Add a new object to the front of the list
		void AddFront(T* const newObject);

		// Add a new object based on the ordering of the object's IDs (object must have GetId() or compiler will complain)
		// WARNNIG: Assumes that the list is already sorted!! Don't call this if it isn't
		void AddSorted(T* const newObject);



		// Get the number of elements in this list
		const int GetNumberOfElements() const;

		
		// Get an iterator to this list
		GenericListIterator<T> GetIterator() const;



		// Remove an object from the list given a pointer to that object
		// Does NOT delete
		bool RemoveByObject(T* const toBeRemoved);

		// Remove an object from the list given
		// Does NOT delete
		T* const RemoveById(const unsigned int idToRemove);

		// Remove the first element in the list
		T* const RemoveFront();


		// Removes every node from the list
		// Contained objects are not deleted
		void Clear();



		// Find the object by its ID. Does not remove anything
		T* const FindById(const unsigned int queriedId) const;


	private:

		//
		// Private Routines
		//


		void AddAfter(GenericListNode<T>* newNode, GenericListNode<T>* nodeBeforeNewNode);
		void AddBefore(GenericListNode<T>* newNode, GenericListNode<T>* nodeAfterNewNode);
		void RemoveNode(GenericListNode<T>* oldNode);

		//
		// Data
		//

		GenericListNode<T>* head;
		int numElements;



		//
		// Deleted Methods
		//

		// No copy
		GenericList(const GenericList& other) = delete;

		// No assignment
		GenericList& operator=(const GenericList& other) = delete;
	};

	
}

#endif