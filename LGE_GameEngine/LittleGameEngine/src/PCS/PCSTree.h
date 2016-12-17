#ifndef PCSTREE_H
#define PCSTREE_H

namespace lge
{
	// Simple data structure
	struct PCSTreeInfo
	{
		int currNumNodes;
		int maxNumNodes;
		int currNumLevels;
		int maxNumLevels;

		PCSTreeInfo() :
			currNumNodes(0),
			maxNumNodes(0),
			currNumLevels(0),
			maxNumLevels(0)
		{
		}
	};




	// forward declare
	class PCSNode;





	// Parent-Child-Sibling Tree
	class PCSTree
	{
	public:
		// constructor
		PCSTree();

		// destructor
		~PCSTree();

		// get Root
		PCSNode* const getRoot() const;

		// insert
		void insert(PCSNode * const inNode, PCSNode * const parent);

		// remove
		void remove(PCSNode * const inNode);

		// get info
		void getInfo(PCSTreeInfo &info);
		void printTree() const;
		const int getNumberOfNodes() const;

	private:

		void IncrementNode();
		void DecrementNode();
		void IncrementLevel();
		void DecrementLevel();

		// Itr pointer corrections for node removal
		void correctItrPointersWithNextSibling(PCSNode* oldNode);
		void correctItrPointersNoNextSibling(PCSNode* oldNode);
		PCSNode* getForwardAfterChildrenOf(PCSNode* target);

		// copy constructor 
		PCSTree(const PCSTree &in);

		// assignment operator
		PCSTree & operator = (const PCSTree &in);

		// Data
		PCSNode     *root;
		PCSTreeInfo mInfo;
		
	};

}

#endif