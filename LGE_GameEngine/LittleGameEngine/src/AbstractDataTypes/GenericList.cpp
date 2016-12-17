#include "GenericList.h"
#include <cassert>

namespace lge
{
	template<typename T>
	GenericList<T>::GenericList() :
		head(nullptr),
		numElements(0)
	{
	}

	template<typename T>
	GenericList<T>::~GenericList()
	{
	}



	// Add a new object to the front of the list
	template<typename T>
	void GenericList<T>::AddFront(T* const newObject)
	{
		assert(newObject != nullptr);
		GenericListNode<T>* newNode = new GenericListNode<T>(newObject);

		// If there is no head
		if (this->head == nullptr)
		{
			assert(this->numElements == 0);

			this->head = newNode;
		}
		// If there is a head
		else
		{
			assert(this->numElements != 0);

			this->head->SetPrevNode(newNode);
			newNode->SetNextNode(this->head);

			this->head = newNode;
		}

		// Increment
		this->numElements++;
	}

	// Add a new object based on the ordering of the object's IDs (object must have GetId() or compiler will complain)
	template<typename T>
	void GenericList<T>::AddSorted(T* const newObject)
	{
		assert(newObject != nullptr);
		GenericListNode<T>* newNode = new GenericListNode<T>(newObject);

		// Search for the node that newNode should be added before
		GenericListNode<T>* currNode = this->head;
		while (currNode != nullptr)
		{
			if (currNode->GetDataObjectId() > newNode->GetDataObjectId())
			{
				break;
			}

			currNode = currNode->GetNextNode();
		}


		// If there was a node to add before newNode
		if (currNode != nullptr)
		{
			// Add the new node before the current node
			this->AddBefore(newNode, currNode);
		}
		// If the newNode is bigger then everyone
		else
		{
			// Add the new node after the current node
			this->AddAfter(newNode, currNode);
		}


		// Increment
		this->numElements++;
	}







	// Get the number of elements in this list
	template<typename T>
	const int GenericList<T>::GetNumberOfElements() const
	{
		return this->numElements;
	}




	// Get an iterator to this list
	template<typename T>
	GenericListIterator<T> GenericList<T>::GetIterator() const
	{
		return GenericListIterator<T>(this->head);
	}






	// Remove an object from the list given a pointer to that object
	// Does NOT delete the object
	template<typename T>
	bool GenericList<T>::RemoveByObject(T* const toBeRemoved)
	{
		// Search the list for an node that holds the same reference
		GenericListNode<T>* currNode = this->head;
		while (currNode != nullptr)
		{
			if (currNode->GetDataObject() == toBeRemoved)
			{
				// Found the node
				break;
			}

			currNode = currNode->GetNextNode();
		}

		// If the node was found
		if (currNode != nullptr)
		{
			this->RemoveNode(currNode);
			this->numElements--;
			return true;
		}

		// If the node wasn't found
		return false;
	}

	// Remove an object from the list given
	// Does NOT delete the object
	template<typename T>
	T* const GenericList<T>::RemoveById(const unsigned int idToRemove)
	{
		// Search the list for an node that holds the same ID
		GenericListNode<T>* currNode = this->head;
		while (currNode != nullptr)
		{
			if (currNode->GetDataObjectId() == idToRemove)
			{
				// Found the node
				break;
			}

			currNode = currNode->GetNextNode();
		}

		// If the node was found
		if (currNode != nullptr)
		{
			T* const removedObject = currNode->GetDataObject();
			this->RemoveNode(currNode);
			this->numElements--;
			assert(removedObject != nullptr);
			return removedObject;
		}

		// If the node wasn't found
		return nullptr;
	}

	// Remove the first element in the list
	// Does NOT delete the object
	template<typename T>
	T* const GenericList<T>::RemoveFront()
	{
		// If there is no head
		if (this->head == nullptr)
		{
			assert(this->numElements == 0);
			return nullptr;
		}

		// If there is a head
		T* const removedObject = this->head->GetDataObject();
		this->RemoveNode(this->head);
		this->numElements--;
		assert(removedObject != nullptr);
		return removedObject;
	}



	// Removes every node from the list
	// Contained objects are not deleted
	template<typename T>
	void GenericList<T>::Clear()
	{
		while (this->head != nullptr)
		{
			this->RemoveNode(this->head);
			this->numElements--;
		}
	}




	// Find the object by its ID. Does not remove anything
	template<typename T>
	T* const GenericList<T>::FindById(const unsigned int queriedId) const
	{
		// Search the list for an node that holds the same ID
		GenericListNode<T>* currNode = this->head;
		while (currNode != nullptr)
		{
			if (currNode->GetDataObjectId() == queriedId)
			{
				// Found the node
				break;
			}

			currNode = currNode->GetNextNode();
		}

		// If the node was found
		if (currNode != nullptr)
		{
			return currNode->GetDataObject();
		}

		// If the node wasn't found
		return nullptr;
	}




	//
	// Private Methods (should not change the "numElements" variable)
	//

	// Does not create a new node or increment numElement
	template<typename T>
	void GenericList<T>::AddAfter(GenericListNode<T>* newNode, GenericListNode<T>* nodeBeforeNewNode)
	{
		assert(nodeBeforeNewNode != nullptr);
		assert(newNode != nullptr);

		// If there is nothing after the "nodeBeforeNewNode"
		if (nodeBeforeNewNode->GetNextNode() == nullptr)
		{
			nodeBeforeNewNode->SetNextNode(newNode);
			newNode->SetPrevNode(nodeBeforeNewNode);

			// Just in case
			newNode->SetNextNode(nullptr);
		}
		// If there is something after the "nodeBeforeNewNode"
		else
		{
			newNode->SetNextNode(nodeBeforeNewNode->GetNextNode());
			nodeBeforeNewNode->GetNextNode()->SetPrevNode(newNode);
			newNode->SetPrevNode(nodeBeforeNewNode);
			nodeBeforeNewNode->SetNextNode(newNode);
		}

	}


	// Does not create a new node or increment numElement
	template<typename T>
	void GenericList<T>::AddBefore(GenericListNode<T>* newNode, GenericListNode<T>* nodeAfterNewNode)
	{
		assert(nodeAfterNewNode != nullptr);
		assert(newNode != nullptr);

		// If there is nothing before the "nodeAfterNewNode"
		if (nodeAfterNewNode->GetPrevNode() == nullptr)
		{
			// nodeAfterNewNode must be the head
			assert(nodeAfterNewNode == this->head);

			assert(this->numElements != 0);

			this->head->SetPrevNode(newNode);
			newNode->SetNextNode(this->head);

			this->head = newNode;
		}
		// There is something before the new node
		else
		{
			newNode->SetNextNode(nodeAfterNewNode);
			newNode->SetPrevNode(nodeAfterNewNode->GetPrevNode());

			nodeAfterNewNode->GetPrevNode()->SetNextNode(newNode);
			nodeAfterNewNode->SetPrevNode(newNode);
		}
	}


	// Does not decrement numElement,
	// but will nullify the head pointer, and delete the old node
	template<typename T>
	void GenericList<T>::RemoveNode(GenericListNode<T>* oldNode)
	{
		assert(oldNode != nullptr);

		// If solo node
		if (oldNode->GetNextNode() == nullptr && oldNode->GetPrevNode() == nullptr)
		{
			// Nullify the head pointer
			this->head = nullptr;
		}
		// If first node
		else if (oldNode->GetNextNode() != nullptr && oldNode->GetPrevNode() == nullptr)
		{
			// oldNode should be the head here!
			assert(this->head == oldNode);

			this->head = this->head->GetNextNode();
			this->head->SetPrevNode(nullptr);

			oldNode->SetNextNode(nullptr);
		}
		// If last node
		else if (oldNode->GetNextNode() == nullptr && oldNode->GetPrevNode() != nullptr)
		{
			oldNode->GetPrevNode()->SetNextNode(nullptr);
			oldNode->SetPrevNode(nullptr);
		}
		// If a middle node
		else if (oldNode->GetNextNode() != nullptr && oldNode->GetPrevNode() != nullptr)
		{
			oldNode->GetPrevNode()->SetNextNode(oldNode->GetNextNode());
			oldNode->GetNextNode()->SetPrevNode(oldNode->GetPrevNode());

			oldNode->SetNextNode(nullptr);
			oldNode->SetPrevNode(nullptr);
		}
		// Shouldn't really be here
		else
		{
			// Unhandled case for list node deletion!!
			assert(false);
		}

		// If you're here, the node was unlinked. Now delete the node.
		// The object in the node should never be deleted
		delete oldNode;
	}
}









#include "..\GraphicsSystem\Shader.h"
#include "..\GraphicsSystem\MaterialUniform.h"
#include "..\GraphicsSystem\MaterialTextureLink.h"
#include "..\GraphicsSystem\Camera.h"
#include "..\GraphicsSystem\Material.h"
#include "..\GraphicsSystem\Mesh.h"
#include "..\GraphicsSystem\Texture.h"
#include "..\AnimationSystem\AnimationSet.h"

namespace lge
{
	//
	// Template Declarations
	//

	// Predeclare the classes that will be put into this GenericList here:
	template class GenericList<Shader>;
	template class GenericList<MaterialUniform>;
	template class GenericList<MaterialTextureLink>;
	template class GenericList < Camera >;
	template class GenericList < Material >;
	template class GenericList < Mesh >;
	template class GenericList < Texture >;
	template class GenericList < AnimationSet >;
}