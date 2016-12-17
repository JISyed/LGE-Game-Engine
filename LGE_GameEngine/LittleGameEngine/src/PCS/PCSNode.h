#ifndef PCSNODE_H
#define PCSNODE_H

#define PCSNODE_NAME_SIZE (20)
#define PCSNODE_VERSION 2.1

namespace lge
{
	// Return codes for PCSNode
	enum PCSNodeReturnCode
	{
		PCSNode_SUCCESS,
		PCSNode_FAIL_NULL_PTR,
		PCSNode_FAIL_RETURN_NOT_INITIALIZED,
		PCSNode_DWORD = 0x7fffffff
	};


	// Represents a node on a Parent-Child-Sibling Tree
	class PCSNode
	{
	public:
		// constructor
		PCSNode();

		// copy constructor
		PCSNode(const PCSNode &in);

		// Specialize Constructor
		PCSNode(const char * const inName);

		// destructor
		virtual ~PCSNode();

		// assignment operator
		PCSNode &operator = (const PCSNode &in);

		// accessors
		void setParent(PCSNode * const in);
		void setChild(PCSNode * const in);
		void setNextSibling(PCSNode * const in);
		void setPrevSibling(PCSNode * const in);
		void setForward(PCSNode * const in);
		void setReverse(PCSNode * const in);

		PCSNode* getParent() const;
		PCSNode* getChild() const;
		PCSNode* getNextSibling() const;
		PCSNode* getPrevSibling() const;
		PCSNode* getForward() const;
		PCSNode* getReverse() const;

		// name
		PCSNodeReturnCode setName(const char * const inName);
		PCSNodeReturnCode getName(char * const outBuffer, unsigned int sizeOutBuffer) const;

		// print
		void printNode() const;
		void printChildren() const;
		void printSiblings() const;

		// get number of children/siblings
		int getNumSiblings() const;
		int getNumChildren() const;

	private:
		PCSNode *parent;
		PCSNode *child;
		PCSNode *nextSibling;
		PCSNode *prevSibling;
		PCSNode *forward;
		PCSNode *reverse;

		char     name[PCSNODE_NAME_SIZE];
	};
}

#endif