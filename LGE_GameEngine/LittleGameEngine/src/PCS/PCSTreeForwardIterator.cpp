#include <assert.h>
#include "PCSTreeForwardIterator.h"
#include "PCSTree.h"

namespace lge
{
	PCSTreeForwardIterator::PCSTreeForwardIterator(const PCSTree& pcsTree) :
		root(pcsTree.getRoot()),
		current(nullptr)
	{
		if (this->root != nullptr)
		{
			this->current = this->root->getForward();
		}
	}

	PCSNode* const PCSTreeForwardIterator::First()
	{
		this->current = this->root->getForward();
		return this->current;
	}

	PCSNode* const PCSTreeForwardIterator::Next()
	{
		if (!this->IsDone())
		{
			this->current = this->current->getForward();
		}
		return this->current;
	}

	const bool PCSTreeForwardIterator::IsDone() const
	{
		return this->current == nullptr;
	}

	PCSNode* const PCSTreeForwardIterator::CurrentItem() const
	{
		return this->current;
	}
}