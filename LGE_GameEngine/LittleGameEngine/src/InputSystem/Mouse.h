#ifndef LGE_MOUSE_H
#define LGE_MOUSE_H

#include "enumMouseButton.h"

namespace lge
{
	namespace Input
	{
		// Used to inquire user input from the keyboard
		class Mouse
		{
		public:

			//
			// Ctor / Dtor
			//

			// Only the Game class should be calling the constructor
			Mouse();
			~Mouse();


			//
			// Methods
			//

			// Only the Game class should update states
			void UpdateStates();




			//
			// Static Methods
			//

			static const bool GetButton(const Input::MouseButton button);
			static const bool GetButtonDown(const Input::MouseButton button);
			static const bool GetButtonUp(const Input::MouseButton button);

			// Gets the mouse in screen space
			static void GetMousePosition(float& x, float& y);

			// Gets the mouse in screen space
			static void GetMousePosition(int& x, int& y);

			static const int GetMousePositionXi();
			static const int GetMousePositionYi();

			static const float GetMousePositionXf();
			static const float GetMousePositionYf();

			// Returned normalized mouse position
			static const float GetPositionNormalizedX();
			static const float GetPositionNormalizedY();

			// Gets absolute state of the mouse wheel
			static const int GetMouseWheel();

			// Gets the relative change in the mouse wheel per frame
			static const int GetMouseWheelDelta();

			

		private:

			//
			// Data
			//

			char prevButtonState[LAST_MOUSE_BUTTON_VALUE];
			int prevWheelState;




			//
			// Static Data
			//

			static Mouse* singetonInstance;





			//
			// Deleted Methods
			//

			// No copy ctor
			Mouse(const Mouse& other) = delete;

			// No copy assignment
			Mouse& operator=(const Mouse& other) = delete;

			// No move ctor
			Mouse(Mouse&& other) = delete;

			// No move assignment
			Mouse& operator=(Mouse&& other) = delete;
		};

		
	}
}
#endif