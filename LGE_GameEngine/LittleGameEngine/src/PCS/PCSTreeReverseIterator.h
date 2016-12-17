#ifndef PCSTREE_REVERSE_ITERATOR_H
#define PCSTREE_REVERSE_ITERATOR_H

#include "PCSTreeIterator.h"

namespace lge
{
	// Forward declare
	class PCSTree;

	// Iterator that moves backwards in a Parent-Child-Sibling Tree
	class PCSTreeReverseIterator : public PCSTreeIterator
	{
	public:

		// Ctor
		PCSTreeReverseIterator(const PCSTree& pcsTree);

		// Contracts
		virtual PCSNode* const First() override;
		virtual PCSNode* const Next() override;
		virtual const bool IsDone() const override;
		virtual PCSNode* const CurrentItem() const override;

	private:

		PCSNode* const root;
		PCSNode* current;

		PCSTreeReverseIterator& operator=(const PCSTreeReverseIterator& o) = delete;
	};
}

#endif;