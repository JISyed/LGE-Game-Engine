#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "PCSTree.h"
#include "PCSNode.h"

namespace lge
{
	// constructor
	PCSNode::PCSNode() :
		parent(nullptr),
		child(nullptr),
		nextSibling(nullptr),
		prevSibling(nullptr),
		forward(nullptr),
		reverse(nullptr)
	{
		memset(this->name, 0x0, PCSNODE_NAME_SIZE);
	}

	// copy constructor
	PCSNode::PCSNode(const PCSNode &in) :
		parent(in.parent),
		child(in.child),
		nextSibling(in.nextSibling),
		prevSibling(in.prevSibling),
		forward(in.forward),
		reverse(in.reverse)
	{
		memcpy(this->name, in.name, PCSNODE_NAME_SIZE);
	}



	PCSNode::PCSNode(const char * const inName) :
		parent(nullptr),
		child(nullptr),
		nextSibling(nullptr),
		prevSibling(nullptr),
		forward(nullptr),
		reverse(nullptr)
	{
		// Check for bad parameter
		if (inName == nullptr)
		{
			// Use zero-ed out array instead
			memset(this->name, 0x0, PCSNODE_NAME_SIZE);
		}

		strcpy_s(this->name, PCSNODE_NAME_SIZE, inName);
		// Null terminator
		this->name[PCSNODE_NAME_SIZE - 1] = '\0';
	}

	// destructor
	PCSNode::~PCSNode()
	{
	}

	// assignment operator
	PCSNode &PCSNode::operator = (const PCSNode &in)
	{
		// Check if you're trying to assign to yourself
		if (this == &in)
		{
			// Skip
			return *this;
		}

		this->parent = in.parent;
		this->child = in.child;
		this->nextSibling = in.nextSibling;
		this->prevSibling = in.prevSibling;
		this->forward = in.forward;
		this->reverse = in.reverse;

		memcpy(this->name, in.name, PCSNODE_NAME_SIZE);

		return *this;
	}


	void PCSNode::setParent(PCSNode * const in)
	{
		this->parent = in;
	}

	void PCSNode::setChild(PCSNode * const in)
	{
		this->child = in;
	}

	void PCSNode::setNextSibling(PCSNode * const in)
	{
		this->nextSibling = in;
	}

	void PCSNode::setPrevSibling(PCSNode * const in)
	{
		this->prevSibling = in;
	}

	void PCSNode::setForward(PCSNode * const in)
	{
		this->forward = in;
	}

	void PCSNode::setReverse(PCSNode * const in)
	{
		this->reverse = in;
	}

	PCSNode* PCSNode::getParent() const
	{
		return this->parent;
	}

	PCSNode* PCSNode::getChild() const
	{
		return this->child;
	}

	PCSNode* PCSNode::getNextSibling() const
	{
		return this->nextSibling;
	}

	PCSNode* PCSNode::getPrevSibling() const
	{
		return this->prevSibling;
	}

	PCSNode* PCSNode::getForward() const
	{
		return this->forward;
	}

	PCSNode* PCSNode::getReverse() const
	{
		return this->reverse;
	}

	PCSNodeReturnCode PCSNode::setName(const char * const inName)
	{
		// Check for invalid parameter
		if (inName == nullptr)
		{
			return PCSNode_FAIL_NULL_PTR;
		}

		size_t inSize = strlen(inName) + 1;

		// inName is too short
		if (inSize < PCSNODE_NAME_SIZE)
		{
			memcpy(this->name, inName, inSize);
			this->name[PCSNODE_NAME_SIZE - 1] = '\0';
		}
		// inName is bigger
		else
		{
			memcpy(this->name, inName, PCSNODE_NAME_SIZE);
			this->name[PCSNODE_NAME_SIZE - 1] = '\0';
		}

		return PCSNode_SUCCESS;
	}


	PCSNodeReturnCode PCSNode::getName(char * const outBuffer, unsigned int sizeOutBuffer) const
	{
		// Check for invalid parameter
		if (outBuffer == nullptr)
		{
			return PCSNode_FAIL_NULL_PTR;
		}

		// Out buffer is too small
		if (sizeOutBuffer < PCSNODE_NAME_SIZE)
		{
			memcpy(outBuffer, this->name, sizeOutBuffer);
			outBuffer[sizeOutBuffer - 1] = '\0';
		}
		// Out buffer is bigger
		else
		{
			memcpy(outBuffer, this->name, PCSNODE_NAME_SIZE);
			outBuffer[PCSNODE_NAME_SIZE - 1] = '\0';
		}

		return PCSNode_SUCCESS;
	}

	void PCSNode::printNode() const
	{
		printf("\n        name: %s", this->name);
		printf("\n        addr: 0x%08X", this);

		if (this->parent != nullptr)
		{
			printf("\n      parent: %s (0x%08X)", this->parent->name, this->parent);
		}
		else
		{
			printf("\n      parent: 0 (0x00000000)");
		}

		if (this->child != nullptr)
		{
			printf("\n       child: %s (0x%08X)", this->child->name, this->child);
		}
		else
		{
			printf("\n       child: 0 (0x00000000)");
		}

		if (this->nextSibling != nullptr)
		{
			printf("\n nextSibling: %s (0x%08X)", this->nextSibling->name, this->nextSibling);
		}
		else
		{
			printf("\n nextSibling: 0 (0x00000000)");
		}

		if (this->prevSibling != nullptr)
		{
			printf("\n prevSibling: %s (0x%08X)", this->prevSibling->name, this->prevSibling);
		}
		else
		{
			printf("\n prevSibling: 0 (0x00000000)");
		}

		if (this->forward != nullptr)
		{
			printf("\n forward: %s (0x%08X)", this->forward->name, this->forward);
		}
		else
		{
			printf("\n forward: 0 (0x00000000)");
		}

		if (this->reverse != nullptr)
		{
			printf("\n reverse: %s (0x%08X)", this->reverse->name, this->reverse);
		}
		else
		{
			printf("\n reverse: 0 (0x00000000)");
		}

		printf("\n\n");
	}

	void PCSNode::printChildren() const
	{
		PCSNode* currChild = this->child;
		while (currChild != nullptr)
		{
			currChild->printNode();
			currChild = currChild->nextSibling;
		}
	}

	void PCSNode::printSiblings() const
	{
		// Print all the previous siblings
		PCSNode* currSibling = this->prevSibling;
		while (currSibling != nullptr)
		{
			currSibling->printNode();
			currSibling = currSibling->prevSibling;
		}

		// Print all the next siblings
		currSibling = this->nextSibling;
		while (currSibling != nullptr)
		{
			currSibling->printNode();
			currSibling = currSibling->nextSibling;
		}
	}

	int PCSNode::getNumSiblings() const
	{
		// Count all the previous siblings
		int numPrevSiblings = 0;
		PCSNode* currSibling = this->prevSibling;
		while (currSibling != nullptr)
		{
			numPrevSiblings++;
			currSibling = currSibling->prevSibling;
		}

		// Count all the next siblings
		int numNextSiblings = 0;
		currSibling = this->nextSibling;
		while (currSibling != nullptr)
		{
			numNextSiblings++;
			currSibling = currSibling->nextSibling;
		}

		return numNextSiblings + numPrevSiblings + 1;
	}

	int PCSNode::getNumChildren() const
	{
		// Count all the children
		int totalChildren = 0;
		PCSNode* currChild = this->child;
		while (currChild != nullptr)
		{
			totalChildren++;
			currChild = currChild->nextSibling;
		}

		return totalChildren;
	}

}