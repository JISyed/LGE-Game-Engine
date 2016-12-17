#ifndef PCSTREE_ITERATOR_H
#define PCSTREE_ITERATOR_H

#include "PCSNode.h"

namespace lge
{
	// An iterator for the Parent-Child-Sibling Tree
	// This class is abstract!
	class PCSTreeIterator
	{
	public:
		virtual PCSNode* const First() = 0;
		virtual PCSNode* const Next() = 0;
		virtual const bool IsDone() const = 0;
		virtual PCSNode* const CurrentItem() const = 0;
	};
}

#endif