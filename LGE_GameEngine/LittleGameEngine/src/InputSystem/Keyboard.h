#ifndef LGE_KEYBOARD_H
#define LGE_KEYBOARD_H

#include "enumKey.h"

namespace lge
{
	namespace Input
	{
		// Used to inquire user input from the keyboard
		class Keyboard
		{
		public:

			//
			// Ctor / Dtor
			//

			// Only the Game class should be calling the constructor
			Keyboard();
			~Keyboard();


			//
			// Methods
			//

			// Only the Game class should update states
			void UpdateStates();


			//
			// Static Methods
			//

			static const bool GetKey(const Input::Key key);
			static const bool GetKeyDown(const Input::Key key);
			static const bool GetKeyUp(const Input::Key key);
			



		private:
			
			//
			// Data
			//

			char prevKeyState[LAST_KEY_VALUE];

			


			//
			// Static Data
			//

			static Keyboard* singetonInstance;






			//
			// Deleted Methods
			//

			// No copy ctor
			Keyboard(const Keyboard& other) = delete;

			// No copy assignment
			Keyboard& operator=(const Keyboard& other) = delete;

			// No move ctor
			Keyboard(Keyboard&& other) = delete;

			// No move assignment
			Keyboard& operator=(Keyboard&& other) = delete;
		};

		
	}
}

#endif