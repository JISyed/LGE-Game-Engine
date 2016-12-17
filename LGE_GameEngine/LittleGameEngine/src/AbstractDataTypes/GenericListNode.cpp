#include "GenericListNode.h"



namespace lge
{
	template<typename T>
	GenericListNode<T>::GenericListNode(T* const newObject) :
		nextNode(nullptr),
		object(newObject),
		objectId(newObject->GetId()),
		prevNode(nullptr)
	{
	}

	template<typename T>
	GenericListNode<T>::GenericListNode(GenericListNode<T>* const newNext,
										GenericListNode<T>* const newPrev,
										T* const newObject) :
										nextNode(newNext),
										object(newObject),
										objectId(newObject->GetId()),
										prevNode(newPrev)
	{
	}

	template<typename T>
	GenericListNode<T>::~GenericListNode()
	{
	}



	template<typename T>
	GenericListNode<T>* const GenericListNode<T>::GetNextNode() const
	{
		return this->nextNode;
	}

	template<typename T>
	GenericListNode<T>* const GenericListNode<T>::GetPrevNode() const
	{
		return this->prevNode;
	}

	template<typename T>
	T* const GenericListNode<T>::GetDataObject() const
	{
		return this->object;
	}

	template<typename T>
	const unsigned int GenericListNode<T>::GetDataObjectId() const
	{
		return this->objectId;
	}



	template<typename T>
	void GenericListNode<T>::SetNextNode(GenericListNode<T>* const newNext)
	{
		this->nextNode = newNext;
	}

	template<typename T>
	void GenericListNode<T>::SetPrevNode(GenericListNode<T>* const newPrev)
	{
		this->prevNode = newPrev;
	}

	template<typename T>
	void GenericListNode<T>::SetObject(T* const newObject)
	{
		this->object = newObject;
		this->objectId = object->GetId();
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

	// Predeclare the classes that will be put into this GenericListNode here:
	template class GenericListNode<Shader>;
	template class GenericListNode<MaterialUniform>;
	template class GenericListNode<MaterialTextureLink>;
	template class GenericListNode < Camera > ;
	template class GenericListNode < Material >;
	template class GenericListNode < Mesh > ;
	template class GenericListNode < Texture > ;
	template class GenericListNode < AnimationSet >;
}