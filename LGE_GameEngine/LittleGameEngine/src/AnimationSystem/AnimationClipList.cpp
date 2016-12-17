#include "AnimationClipList.h"
#include <cassert>
#include <cstring>

namespace lge
{
	//
	// Node
	//

	AnimationClipList::Node::Node() :
		next(nullptr),
		prev(nullptr),
		data(nullptr)
	{
	}

	AnimationClipList::Node::Node(AnimationClip* const newClip) :
		next(nullptr),
		prev(nullptr),
		data(newClip)
	{
	}

	AnimationClipList::Node::Node(AnimationClip* const newClip, Node* const nextNode, Node* const previousNode) :
		next(nextNode),
		prev(previousNode),
		data(newClip)
	{
	}

	AnimationClipList::Node::~Node()
	{
		if (this->data != nullptr)
		{
			delete this->data;
		}
	}

	AnimationClipList::Node* const AnimationClipList::Node::GetNext() const
	{
		return this->next;
	}

	AnimationClipList::Node* const AnimationClipList::Node::GetPrev() const
	{
		return this->prev;
	}

	AnimationClip* const AnimationClipList::Node::GetData() const
	{
		return this->data;
	}


	void AnimationClipList::Node::SetNext(AnimationClipList::Node* const newNext)
	{
		this->next = newNext;
	}

	void AnimationClipList::Node::SetPrev(AnimationClipList::Node* const newPrev)
	{
		this->prev = newPrev;
	}

	void AnimationClipList::Node::SetData(AnimationClip* const newClip)
	{
		this->data = newClip;
	}




	//
	// Iterator
	//


	AnimationClipList::Iterator::Iterator(AnimationClipList::Node* const headNode) :
		first(headNode),
		current(headNode)
	{
	}

	AnimationClipList::Iterator::Iterator(const Iterator& other) :
		first(other.first),
		current(other.current)
	{
	}

	AnimationClipList::Iterator::~Iterator()
	{
	}

	AnimationClip* const AnimationClipList::Iterator::GetFirst() const
	{
		return this->first->GetData();
	}

	void AnimationClipList::Iterator::GoToNext()
	{
		this->current = this->current->GetNext();
	}

	AnimationClip* const AnimationClipList::Iterator::GetCurrent() const
	{
		return this->current->GetData();
	}

	void AnimationClipList::Iterator::Reset()
	{
		this->current = this->first;
	}

	const bool AnimationClipList::Iterator::IsDone() const
	{
		return this->current == nullptr;
	}





	//
	// List
	//

	AnimationClipList::AnimationClipList() :
		head(nullptr),
		tail(nullptr),
		numNodes(0u)
	{
	}

	AnimationClipList::~AnimationClipList()
	{
		this->Clear();
	}


	void AnimationClipList::AddToBack(AnimationClip* const newClip)
	{
		AnimationClipList::Node* newNode = new AnimationClipList::Node(newClip);
		this->AddNodeToBack(newNode);
	}

	const unsigned int AnimationClipList::GetNumberOfClips() const
	{
		return this->numNodes;
	}

	AnimationClipList::Iterator AnimationClipList::GetIterator() const
	{
		return Iterator(this->head);
	}

	void AnimationClipList::Clear()
	{
		while (this->head != nullptr)
		{
			this->RemoveNodeOnBack();
		}
	}


	const AnimationClip* const AnimationClipList::FindClipById(const unsigned int id) const
	{
		const AnimationClip* inquired = nullptr;

		for (auto itr = this->GetIterator(); !itr.IsDone(); itr.GoToNext())
		{
			const AnimationClip* currentClip = itr.GetCurrent();
			assert(currentClip != nullptr);
			if (currentClip->GetId() == id)
			{
				// Found!
				inquired = currentClip;
				break;
			}
		}

		return inquired;
	}

	const AnimationClip* const AnimationClipList::FindClipByName(const char* const name) const
	{
		const AnimationClip* inquired = nullptr;

		for (auto itr = this->GetIterator(); !itr.IsDone(); itr.GoToNext())
		{
			const AnimationClip* currentClip = itr.GetCurrent();
			assert(currentClip != nullptr);
			if (0 == std::strcmp(currentClip->GetName(), name))
			{
				// Found!
				inquired = currentClip;
				break;
			}
		}

		return inquired;
	}




	void AnimationClipList::AddNodeToBack(AnimationClipList::Node* const newNode)
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

	void AnimationClipList::RemoveNodeOnBack()
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