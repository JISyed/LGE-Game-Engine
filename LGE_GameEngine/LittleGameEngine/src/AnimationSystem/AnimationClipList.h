#ifndef H_LGE_ANIMATION_CLIP_LIST
#define H_LGE_ANIMATION_CLIP_LIST
#include "AnimationClip.h"

namespace lge
{
	class AnimationClipList
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
			Node(AnimationClip* const newClip);
			Node(AnimationClip* const newClip, Node* const nextNode, Node* const previousNode);
			~Node();

			Node* const GetNext() const;
			Node* const GetPrev() const;
			AnimationClip* const GetData() const;

			void SetNext(Node* const newNext);
			void SetPrev(Node* const newPrev);
			void SetData(AnimationClip* const newClip);


		private:

			Node* next;
			Node* prev;
			AnimationClip* data;

		};

	public:

		// The iterator of AnimationClipList
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
			AnimationClip* const GetFirst() const;

			// Go to next modifier without returning
			void GoToNext();

			// Return the current modifier
			AnimationClip* const GetCurrent() const;

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

		AnimationClipList();
		~AnimationClipList();


		//
		// Methods
		//

		void AddToBack(AnimationClip* const newClip);
		const unsigned int GetNumberOfClips() const;
		Iterator GetIterator() const;
		void Clear();
		const AnimationClip* const FindClipById(const unsigned int id) const;
		const AnimationClip* const FindClipByName(const char* const name) const;


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