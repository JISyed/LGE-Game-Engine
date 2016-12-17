#include "GenericListIterator.h"
#include <cassert>

namespace lge
{
	template<typename T>
	GenericListIterator<T>::GenericListIterator(GenericListNode<T>* headNode) :
		currentNode(headNode),
		firstNode(headNode)
	{
		assert(headNode != nullptr);
	}

	template<typename T>
	GenericListIterator<T>::~GenericListIterator()
	{
	}





	template<typename T>
	T* const GenericListIterator<T>::First()
	{
		this->currentNode = this->firstNode;
		return this->firstNode->GetDataObject();
	}

	template<typename T>
	T* const GenericListIterator<T>::Next()
	{
		assert(this->currentNode != nullptr);
		this->currentNode = this->currentNode->GetNextNode();
		if (this->currentNode == nullptr)
		{
			return nullptr;
		}
		return this->currentNode->GetDataObject();
	}

	template<typename T>
	const bool GenericListIterator<T>::IsDone() const
	{
		return this->currentNode == nullptr;
	}

	template<typename T>
	T* const GenericListIterator<T>::CurrentItem() const
	{
		assert(this->currentNode != nullptr);
		return this->currentNode->GetDataObject();
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

	// Predeclare the classes that will be put into this GenericListIterator here:
	template class GenericListIterator<Shader>;
	template class GenericListIterator<MaterialUniform>;
	template class GenericListIterator<MaterialTextureLink>;
	template class GenericListIterator < Camera >;
	template class GenericListIterator < Material >;
	template class GenericListIterator < Mesh >;
	template class GenericListIterator < Texture >;
	template class GenericListIterator < AnimationSet >;
}