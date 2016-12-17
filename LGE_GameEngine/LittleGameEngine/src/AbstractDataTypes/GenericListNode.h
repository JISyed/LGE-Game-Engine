#ifndef LGE_GENERIC_LIST_NODE_H
#define LGE_GENERIC_LIST_NODE_H

namespace lge
{
	// A list node that can only hold objects of type T.
	// Holds the object with aggregation, not composition.
	// The object MUST have the method "const unsigned int GetId() const".
	// Declare what classes will be held in this list by refering to the .cpp file
	template<typename T> class GenericListNode
	{
	public:
		GenericListNode() = delete;
		GenericListNode(T* const newObject);
		GenericListNode(GenericListNode<T>* const newNext, GenericListNode<T>* const newPrev, T* const newObject);
		~GenericListNode();

		GenericListNode<T>* const GetNextNode() const;
		GenericListNode<T>* const GetPrevNode() const;
		T* const GetDataObject() const;
		const unsigned int GetDataObjectId() const;


		void SetNextNode(GenericListNode<T>* const newNext);
		void SetPrevNode(GenericListNode<T>* const newPrev);
		void SetObject(T* const newObject);


	private:

		GenericListNode<T>* nextNode;
		unsigned int objectId;
		T* object;
		GenericListNode<T>* prevNode;
	};

	
}
#endif