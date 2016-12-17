#include <assert.h>
#include "PCSTreeReverseIterator.h"
#include "PCSTree.h"

namespace lge
{
	PCSTreeReverseIterator::PCSTreeReverseIterator(const PCSTree& pcsTree) :
		root(pcsTree.getRoot()),
		current(nullptr)
	{
		if (this->root != nullptr)
		{
			this->current = this->root->getReverse();
		}
	}

	PCSNode* const PCSTreeReverseIterator::First()
	{
		this->current = this->root->getReverse();
		return this->current;
	}

	PCSNode* const PCSTreeReverseIterator::Next()
	{
		if (!this->IsDone())
		{
			this->current = this->current->getReverse();
		}
		return this->current;
	}

	const bool PCSTreeReverseIterator::IsDone() const
	{
		return this->current == nullptr;
	}

	PCSNode* const PCSTreeReverseIterator::CurrentItem() const
	{
		return this->current;
	}
}
