#ifndef PCSTREE_FORWARD_ITERATOR_H
#define PCSTREE_FORWARD_ITERATOR_H

#include "PCSTreeIterator.h"

namespace lge
{
	// Forward declare
	class PCSTree;

	// Iterator that moves forward in a Parent-Child-Sibling Tree
	class PCSTreeForwardIterator : public PCSTreeIterator
	{
	public:

		// Ctor
		PCSTreeForwardIterator(const PCSTree& pcsTree);

		// Contracts
		virtual PCSNode* const First() override;
		virtual PCSNode* const Next() override;
		virtual const bool IsDone() const override;
		virtual PCSNode* const CurrentItem() const override;

	private:

		PCSNode* const root;
		PCSNode* current;

		PCSTreeForwardIterator& operator=(const PCSTreeForwardIterator& o) = delete;
	};
}

#endif;