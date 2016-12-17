#include "AnimationPlaybackList.h"
#include <cassert>

namespace lge
{
	//
	// Node
	//

	AnimationPlaybackList::Node::Node() :
		next(nullptr),
		prev(nullptr),
		data(nullptr)
	{
	}

	AnimationPlaybackList::Node::Node(AnimationPlayback* const newData) :
		next(nullptr),
		prev(nullptr),
		data(newData)
	{
	}

	AnimationPlaybackList::Node::Node(AnimationPlayback* const newData, Node* const nextNode, Node* const previousNode) :
		next(nextNode),
		prev(previousNode),
		data(newData)
	{
	}

	AnimationPlaybackList::Node::~Node()
	{
		if (this->data != nullptr)
		{
			delete this->data;
		}
	}

	AnimationPlaybackList::Node* const AnimationPlaybackList::Node::GetNext() const
	{
		return this->next;
	}

	AnimationPlaybackList::Node* const AnimationPlaybackList::Node::GetPrev() const
	{
		return this->prev;
	}

	AnimationPlayback* const AnimationPlaybackList::Node::GetData() const
	{
		return this->data;
	}


	void AnimationPlaybackList::Node::SetNext(AnimationPlaybackList::Node* const newNext)
	{
		this->next = newNext;
	}

	void AnimationPlaybackList::Node::SetPrev(AnimationPlaybackList::Node* const newPrev)
	{
		this->prev = newPrev;
	}

	void AnimationPlaybackList::Node::SetData(AnimationPlayback* const newData)
	{
		this->data = newData;
	}




	//
	// Iterator
	//


	AnimationPlaybackList::Iterator::Iterator(AnimationPlaybackList::Node* const headNode) :
		first(headNode),
		current(headNode)
	{
	}

	AnimationPlaybackList::Iterator::Iterator(const Iterator& other) :
		first(other.first),
		current(other.current)
	{
	}

	AnimationPlaybackList::Iterator::~Iterator()
	{
	}

	AnimationPlayback* const AnimationPlaybackList::Iterator::GetFirst() const
	{
		return this->first->GetData();
	}

	void AnimationPlaybackList::Iterator::GoToNext()
	{
		this->current = this->current->GetNext();
	}

	AnimationPlayback* const AnimationPlaybackList::Iterator::GetCurrent() const
	{
		return this->current->GetData();
	}

	void AnimationPlaybackList::Iterator::Reset()
	{
		this->current = this->first;
	}

	const bool AnimationPlaybackList::Iterator::IsDone() const
	{
		return this->current == nullptr;
	}





	//
	// List
	//

	AnimationPlaybackList::AnimationPlaybackList() :
		head(nullptr),
		tail(nullptr),
		numNodes(0u)
	{
	}

	AnimationPlaybackList::~AnimationPlaybackList()
	{
		this->Clear();
	}


	void AnimationPlaybackList::AddToBack(AnimationPlayback* const newData)
	{
		AnimationPlaybackList::Node* newNode = new AnimationPlaybackList::Node(newData);
		this->AddNodeToBack(newNode);
	}

	const unsigned int AnimationPlaybackList::GetSizeOfList() const
	{
		return this->numNodes;
	}

	AnimationPlaybackList::Iterator AnimationPlaybackList::GetIterator() const
	{
		return Iterator(this->head);
	}

	void AnimationPlaybackList::Clear()
	{
		while (this->head != nullptr)
		{
			this->RemoveNodeOnBack();
		}
	}


	AnimationPlayback* const AnimationPlaybackList::FindDataById(const unsigned int id) const
	{
		AnimationPlayback* inquired = nullptr;

		for (auto itr = this->GetIterator(); !itr.IsDone(); itr.GoToNext())
		{
			AnimationPlayback* currentData = itr.GetCurrent();
			assert(currentData != nullptr);
			if (currentData->GetPlaybackNameHash() == id)
			{
				// Found!
				inquired = currentData;
				break;
			}
		}

		return inquired;
	}

	AnimationPlayback* const AnimationPlaybackList::FindDataByName(const char* const name) const
	{
		AnimationPlayback* inquired = nullptr;

		for (auto itr = this->GetIterator(); !itr.IsDone(); itr.GoToNext())
		{
			AnimationPlayback* currentData = itr.GetCurrent();
			assert(currentData != nullptr);
			//if (0 == std::strcmp(currentData->GetPlaybackName(), name))
			if (currentData->GetPlaybackName() == name)
			{
				// Found!
				inquired = currentData;
				break;
			}
		}

		return inquired;
	}




	void AnimationPlaybackList::AddNodeToBack(AnimationPlaybackList::Node* const newNode)
	{
		if (this->head == nullptr)
		{
			assert(this->numNodes == 0u);
			assert(this->tail == nullptr);
			this->head = newNode;
			this->tail = newNode;
			this->head->SetNext(nullptr);
			this->head->SetPrev(nullptr);
		}
		else
		{
			if (this->numNodes == 1u)
			{
				this->tail = newNode;
				this->tail->SetNext(nullptr);
				this->tail->SetPrev(this->head);
				this->head->SetNext(this->tail);
			}
			else
			{
				this->tail->SetNext(newNode);
				newNode->SetPrev(this->tail);
				this->tail = newNode;
			}
		}

		this->numNodes++;
	}

	void AnimationPlaybackList::RemoveNodeOnBack()
	{
		assert(this->numNodes > 0u);
		assert(this->head != nullptr);
		assert(this->tail != nullptr);

		if (this->head == this->tail)
		{
			Node* toBeRemoved = this->head;
			this->head = nullptr;
			this->tail = nullptr;
			delete toBeRemoved;
		}
		else
		{
			assert(this->numNodes >= 2u);
			if (this->numNodes == 2u)
			{
				Node* toBeRemoved = this->tail;
				assert(this->head->GetNext() == this->tail);
				this->head->SetNext(nullptr);
				this->tail = this->head;
				delete toBeRemoved;
			}
			else
			{
				assert(this->head->GetNext() != this->tail);
				Node* toBeRemoved = this->tail;
				this->tail->GetPrev()->SetNext(nullptr);
				this->tail = toBeRemoved->GetPrev();
				delete toBeRemoved;
			}
		}

		this->numNodes--;
	}
}