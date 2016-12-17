#ifndef LGE_GENERIC_LIST_ITERATOR_H
#define LGE_GENERIC_LIST_ITERATOR_H

#include "GenericListNode.h"

namespace lge
{
	// Forward Iterator used to access element of GenericList
	// See "GenericList" and "GenericListNode" for more information
	template<typename T> class GenericListIterator
	{
	public:
		GenericListIterator(GenericListNode<T>* headNode);
		~GenericListIterator();

		// Move to the first node and return it
		T* const First();

		// Go to the next node and return it
		T* const Next();

		// Use this to check if looping through iteration is done.
		// Stop iterating if this returns true.
		const bool IsDone() const;

		// Get the current item pointed by this iterator.
		// Do NOT call if IsDone() returns true!
		T* const CurrentItem() const;

	private:

		GenericListNode<T>* currentNode;
		GenericListNode<T>* const firstNode;


		// No assignment
		GenericListIterator& operator=(const GenericListIterator& other) = delete;
	};

	
}
#endif