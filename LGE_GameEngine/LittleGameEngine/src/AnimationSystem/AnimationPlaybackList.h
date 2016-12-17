#ifndef H_LGE_ANIMATION_PLAYBACK_LIST
#define H_LGE_ANIMATION_PLAYBACK_LIST
#include "AnimationPlayback.h"

namespace lge
{
	class AnimationPlaybackList
	{
		///////////////
		// Begin Nested Classes
		///////////////

	private:

		// The internal node of AnimationClipList
		class Node
		{
		public:
			Node();
			Node(AnimationPlayback* const newData);
			Node(AnimationPlayback* const newData, Node* const nextNode, Node* const previousNode);
			~Node();

			Node* const GetNext() const;
			Node* const GetPrev() const;
			AnimationPlayback* const GetData() const;

			void SetNext(Node* const newNext);
			void SetPrev(Node* const newPrev);
			void SetData(AnimationPlayback* const newData);


		private:

			Node* next;
			Node* prev;
			AnimationPlayback* data;

		};

	public:

		// The iterator of AnimationPlaybackList
		class Iterator
		{
		public:
			// No default Ctor
			Iterator() = delete;
			// Ctor only to be used by the list class
			Iterator(Node* const headNode);
			// Copy Ctor
			Iterator(const Iterator& other);
			// No assignment
			Iterator& operator=(const Iterator& other) = delete;
			// Dtor
			~Iterator();


			// Get the first modifier in this iterator's list
			AnimationPlayback* const GetFirst() const;

			// Go to next modifier without returning
			void GoToNext();

			// Return the current modifier
			AnimationPlayback* const GetCurrent() const;

			// Move iterator back to beginning
			void Reset();

			// Returns true if the iterator cannot continue
			const bool IsDone() const;

		private:

			Node* const first;
			Node* current;
		};





		///////////////
		// Begin List Class
		///////////////

	public:

		//
		// Ctor / Dtor
		//

		AnimationPlaybackList();
		~AnimationPlaybackList();


		//
		// Methods
		//

		void AddToBack(AnimationPlayback* const newData);
		const unsigned int GetSizeOfList() const;
		Iterator GetIterator() const;
		void Clear();
		AnimationPlayback* const FindDataById(const unsigned int id) const;
		AnimationPlayback* const FindDataByName(const char* const name) const;


	private:

		//
		// Data
		//

		Node* head;
		Node* tail;
		unsigned int numNodes;



		//
		// Private Routines
		//

		void AddNodeToBack(Node* const newNode);
		void RemoveNodeOnBack();
	};
}
#endif