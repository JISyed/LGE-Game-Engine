#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "PCSTree.h"
#include "PCSNode.h"
#include "PCSTreeForwardIterator.h"
#include "PCSTreeReverseIterator.h"

namespace lge
{
	//
	// C-Helper Functinos
	//

	// Used to unlink an entire local branch of the tree
	void unlinkBranchesFrom(PCSNode* headNode)
	{
		if (headNode == nullptr)
		{
			assert(headNode != nullptr);
			return;
		}

		PCSNode* currChild = headNode->getChild();
		PCSNode* nextChild = nullptr;
		while (currChild != nullptr)
		{
			nextChild = currChild->getNextSibling();
			// Recursion!
			unlinkBranchesFrom(currChild);
			currChild = nextChild;
		}

		// Unlink local node after unlinking children
		headNode->setParent(nullptr);
		headNode->setChild(nullptr);
		headNode->setNextSibling(nullptr);
		headNode->setPrevSibling(nullptr);

		// Delete node. Assuming that the tree was managing the node in the first place
		delete headNode;
	}


	// Used in tree branch removal
	int getNumberOfChildrenFrom(PCSNode* headNode)
	{
		if (headNode->getChild() == nullptr)
		{
			return 0;
		}

		PCSNode* const firstChild = headNode->getChild();
		PCSNode* currSibling = firstChild;

		int localTotal = 0;
		while (currSibling != nullptr)
		{
			// Recursion!
			int branchTotal = getNumberOfChildrenFrom(currSibling) + 1;
			localTotal += branchTotal;
			currSibling = currSibling->getNextSibling();
		}

		return localTotal;
	}

	// Used to determine if the new node will increment the level or not
	int getDepthByCountingUpFrom(PCSNode* leafNode)
	{
		int depth = 0;

		PCSNode* currNode = leafNode;
		while (currNode != nullptr)
		{
			depth++;
			currNode = currNode->getParent();
		}

		return depth;
	}

	// Recursively figure out the new current level of the tree
	void getNewDepthRecursively(PCSNode* headNode, int& maxDepth)
	{
		// If leaf node
		if (headNode->getChild() == nullptr)
		{
			// Iteratively inquire the depth from local leaf node
			int newDepth = getDepthByCountingUpFrom(headNode);
			if (newDepth > maxDepth)
			{
				maxDepth = newDepth;
			}

			// Then ask the next sibling
			PCSNode* leafSibling = headNode->getNextSibling();
			if (leafSibling != nullptr)
			{
				getNewDepthRecursively(leafSibling, maxDepth);
			}
		}
		// If not leaf node
		else
		{
			// Ask every sibling of the first child
			PCSNode* currChild = headNode->getChild();
			while (currChild != nullptr)
			{
				getNewDepthRecursively(currChild, maxDepth);
				currChild = currChild->getNextSibling();
			}
		}
	}



	//
	// PCSTree Methods
	//

	// constructor
	PCSTree::PCSTree() :
		mInfo(),
		root(nullptr)
	{
	}

	// destructor
	PCSTree::~PCSTree()
	{
		if (this->root != nullptr)
		{
			this->remove(this->root);
		}
	}

	// get Root
	PCSNode* const PCSTree::getRoot() const
	{
		return this->root;
	}

	// Insert
	void PCSTree::insert(PCSNode * const inNode, PCSNode * const base)
	{
		// "parent" parameter will be refered to as "base" node

		// Check for bad value
		if (inNode == nullptr)
		{
			// Leave
			return;
		}

		// If the base is null, inNode is new root
		if (base == nullptr)
		{
			// Root should be null!
			assert(this->root == nullptr);

			this->root = inNode;
			this->IncrementNode();
			this->IncrementLevel();

			this->root->setChild(nullptr);
			this->root->setParent(nullptr);
			this->root->setNextSibling(nullptr);
			this->root->setPrevSibling(nullptr);
			this->root->setForward(nullptr);
			this->root->setReverse(nullptr);
		}
		// For non-empty tree
		else
		{
			// If base node has no children
			if (base->getChild() == nullptr)
			{
				// Check if the inNode would start a new generation
				int newDepth = getDepthByCountingUpFrom(base) + 1;
				if (newDepth > this->mInfo.currNumLevels)
				{
					this->IncrementLevel();
				}

				// inNode is new only child
				base->setChild(inNode);
				inNode->setParent(base);
				this->IncrementNode();

				// Correct forward and reverse pointers...
				// ... If the base is NOT the root
				if (base != this->root)
				{
					// If base has a forward pointer
					if (base->getForward() != nullptr)
					{
						PCSNode* oldForward = base->getForward();
						oldForward->setReverse(inNode);
						inNode->setForward(oldForward);
						inNode->setReverse(base);
						base->setForward(inNode);
					}
					// If base has no forward pointer
					else
					{
						inNode->setForward(nullptr);
						inNode->setReverse(base);
						base->setForward(inNode);
						this->root->setReverse(inNode);
					}
				}
				// ... Or if the base is the root
				else
				{
					inNode->setForward(nullptr);
					inNode->setReverse(nullptr);
					this->root->setForward(inNode);
					this->root->setReverse(inNode);
				}
			}
			// If base node has children
			else
			{
				// inNode is new first sibling
				PCSNode* oldFirstSibling = base->getChild();
				assert(oldFirstSibling->getPrevSibling() == nullptr);
				oldFirstSibling->setPrevSibling(inNode);
				inNode->setNextSibling(oldFirstSibling);
				base->setChild(inNode);
				inNode->setParent(base);
				this->IncrementNode();

				// Correct forward and reverse pointers...
				// ... If the base is NOT the root
				if (base != this->root)
				{
					inNode->setReverse(base);
					inNode->setForward(oldFirstSibling);
					oldFirstSibling->setReverse(inNode);
					base->setForward(inNode);
				}
				// ... Or if the base is the root
				else
				{
					this->root->setForward(inNode);
					inNode->setForward(oldFirstSibling);
					oldFirstSibling->setReverse(inNode);
				}
			}
		}
	}

	// Remove
	void PCSTree::remove(PCSNode * const target)
	{
		// "inNode" was renamed to "target" node

		// Check for bad value
		if (target == nullptr)
		{
			// Leave
			assert(target != nullptr);
			return;
		}

		// If target node has no parent
		if (target->getParent() == nullptr)
		{
			// Non-parent target can only be the root
			assert(target == this->root);
			assert(target->getNextSibling() == nullptr);
			assert(target->getPrevSibling() == nullptr);

			// Remove target
			this->root = nullptr;
			this->mInfo.currNumNodes = 0;
			this->mInfo.currNumLevels = 0;
			unlinkBranchesFrom(target);
		}
		// If target node has parent
		else
		{
			// If target has no siblings
			if (target->getNextSibling() == nullptr && target->getPrevSibling() == nullptr)
			{
				// Calculate number of nodes removed
				int totalRemovedNodes = getNumberOfChildrenFrom(target) + 1;
				this->mInfo.currNumNodes -= totalRemovedNodes;
				assert(this->mInfo.currNumNodes >= 0);

				// Correct iterator pointers before removing node
				this->correctItrPointersNoNextSibling(target);

				// Remove node and its branch
				PCSNode* parentOfTarget = target->getParent();
				parentOfTarget->setChild(nullptr);
				unlinkBranchesFrom(target);

				// Calculate the new level
				int newDepth = 0;
				getNewDepthRecursively(this->root, newDepth);
				this->mInfo.currNumLevels = newDepth;
			}
			// If target is last sibling
			else if (target->getNextSibling() == nullptr)
			{
				// Calculate number of nodes removed
				int totalRemovedNodes = getNumberOfChildrenFrom(target) + 1;
				this->mInfo.currNumNodes -= totalRemovedNodes;
				assert(this->mInfo.currNumNodes >= 0);

				// Correct iterator pointers before removing node
				this->correctItrPointersNoNextSibling(target);

				// Remove node and its branch
				PCSNode* prevSibling = target->getPrevSibling();
				prevSibling->setNextSibling(nullptr);
				unlinkBranchesFrom(target);

				// Calculate the new level
				int newDepth = 0;
				getNewDepthRecursively(this->root, newDepth);
				this->mInfo.currNumLevels = newDepth;
			}
			// If target is first sibling
			else if (target->getPrevSibling() == nullptr)
			{
				// Calculate number of nodes removed
				int totalRemovedNodes = getNumberOfChildrenFrom(target) + 1;
				this->mInfo.currNumNodes -= totalRemovedNodes;
				assert(this->mInfo.currNumNodes >= 0);

				// Correct iterator pointers before removing node
				this->correctItrPointersWithNextSibling(target);

				// Remove node and its local branch
				PCSNode* nextSibling = target->getNextSibling();
				nextSibling->setPrevSibling(nullptr);
				nextSibling->getParent()->setChild(nextSibling);
				unlinkBranchesFrom(target);

				// Calculate the new level
				int newDepth = 0;
				getNewDepthRecursively(this->root, newDepth);
				this->mInfo.currNumLevels = newDepth;
			}
			// If target is a middle sibling
			else
			{
				// Calculate number of nodes removed
				int totalRemovedNodes = getNumberOfChildrenFrom(target) + 1;
				this->mInfo.currNumNodes -= totalRemovedNodes;
				assert(this->mInfo.currNumNodes >= 0);

				// Correct iterator pointers before removing node
				this->correctItrPointersWithNextSibling(target);

				// Remove node and its local branch
				PCSNode* prevSibling = target->getPrevSibling();
				PCSNode* nextSibling = target->getNextSibling();
				prevSibling->setNextSibling(nextSibling);
				nextSibling->setPrevSibling(prevSibling);
				unlinkBranchesFrom(target);

				// Calculate the new level
				int newDepth = 0;
				getNewDepthRecursively(this->root, newDepth);
				this->mInfo.currNumLevels = newDepth;
			}

		}
	}

	// get tree info
	void PCSTree::getInfo(PCSTreeInfo &infoContainer)
	{
		infoContainer.currNumNodes = this->mInfo.currNumNodes;
		infoContainer.maxNumNodes = this->mInfo.maxNumNodes;
		infoContainer.currNumLevels = this->mInfo.currNumLevels;
		infoContainer.maxNumLevels = this->mInfo.maxNumLevels;
	}

	void PCSTree::printTree() const
	{
		// Iterate through every node and print it
		//*
		PCSTreeForwardIterator itr(*this);
		PCSNode* currNode = itr.First();
		while (!itr.IsDone())
		{
			currNode->printNode();
			currNode = itr.Next();
		}
		//*/

		// Reverse iteration
		/*
		PCSTreeReverseIterator ritr(this);
		PCSNode* currNode = ritr.First();
		while (!ritr.IsDone())
		{
		currNode->printNode();
		currNode = ritr.Next();
		}
		//*/
	}

	const int PCSTree::getNumberOfNodes() const
	{
		return this->mInfo.currNumNodes;
	}

	void PCSTree::IncrementNode()
	{
		this->mInfo.currNumNodes++;

		if (this->mInfo.currNumNodes > this->mInfo.maxNumNodes)
		{
			this->mInfo.maxNumNodes = this->mInfo.currNumNodes;
		}
	}

	void PCSTree::DecrementNode()
	{
		this->mInfo.currNumNodes--;
	}

	void PCSTree::IncrementLevel()
	{
		this->mInfo.currNumLevels++;

		if (this->mInfo.currNumLevels > this->mInfo.maxNumLevels)
		{
			this->mInfo.maxNumLevels = this->mInfo.currNumLevels;
		}
	}

	void PCSTree::DecrementLevel()
	{
		this->mInfo.currNumLevels--;
	}



	// Itr pointer corrections for node removal
	void PCSTree::correctItrPointersWithNextSibling(PCSNode* oldNode)
	{
		// Get the node's reverse and nextSibling (reverse can either be parent or prevSibling)
		PCSNode* oldReverse = oldNode->getReverse();
		PCSNode* oldNextSibling = oldNode->getNextSibling();

		// Does the node have a reverse pointer (usually the case)
		if (oldReverse != nullptr)
		{
			oldReverse->setForward(oldNextSibling);
			oldNextSibling->setReverse(oldReverse);
		}
		// Or does the node have no reverse ptr (indicates first sibling under root)
		else
		{
			// The node's parent must be the tree root if we're here
			assert(oldNode->getParent() == this->root);
			oldNextSibling->setReverse(nullptr);
			this->root->setForward(oldNextSibling);
		}
	}

	void PCSTree::correctItrPointersNoNextSibling(PCSNode* oldNode)
	{
		// Get the old reverse (can be either parent or previous sibling)
		PCSNode* oldReverse = oldNode->getReverse();
		PCSNode* oldForward = nullptr;

		// Does the node have a reverse pointer (usually the case)
		if (oldReverse != nullptr)
		{
			// Get the old forward pointer...
			// ... if the node has children
			if (oldNode->getChild() != nullptr)
			{
				oldForward = this->getForwardAfterChildrenOf(oldNode);
			}
			// ... or if the node has no children
			else
			{
				oldForward = oldNode->getForward();
			}

			// If old pointer is null, that means that deleting oldNode
			// would have been the end of forward iteration
			if (oldForward == nullptr)
			{
				// oldReverse is the new last node in forward iteration
				oldReverse->setForward(nullptr);
				this->root->setReverse(nullptr);
			}
			// Here, oldForward is valid, and thus wouldn't end forward iteration
			else
			{
				oldReverse->setForward(oldForward);
				oldForward->setReverse(oldReverse);
			}
		}
		// Or does the node have no reverse ptr (indicates only sibling under root)
		else
		{
			// The node's parent must be the tree root if we're here
			assert(oldNode->getParent() == this->root);

			// Assuming that the node has no other sibling
			assert(oldNode->getPrevSibling() == nullptr);
			assert(oldNode->getNextSibling() == nullptr);

			// Basically removing every child node under the node,
			// so root doesn't point to anyone anymore
			this->root->setForward(nullptr);
			this->root->setReverse(nullptr);
		}
	}

	PCSNode* PCSTree::getForwardAfterChildrenOf(PCSNode* target)
	{
		// Assumption: target has children! (at least 1)
		assert(target->getChild() != nullptr);

		// "currForward" can never be invalid because
		// a target's first child is its foward
		PCSNode* currForward = target->getForward();
		PCSNode* nextForward = currForward->getForward();

		// Traverse through all children until no more forward...
		while (nextForward != nullptr)
		{
			// ... or until nextForward is not directly related to currForward
			if (!(currForward->getChild() == nextForward || currForward->getNextSibling() == nextForward))
			{
				// Stop traversing
				break;
			}

			// Next node
			currForward = nextForward;
			nextForward = nextForward->getForward();
		}

		// If nextForward was null, there would be no forward after target is deleted.
		// But regardless, return the result, null or not
		return nextForward;
	}

}



