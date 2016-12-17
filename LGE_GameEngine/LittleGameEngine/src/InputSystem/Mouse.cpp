#include "Mouse.h"
#include <cassert>
#include "GL\glfw.h"
#include "..\EngineUtilities\Screen.h"

namespace lge
{
	namespace Input
	{
		//
		// Static Data
		//

		Mouse* Mouse::singetonInstance = nullptr;




		//
		// Methods
		//

		Mouse::Mouse() : 
			prevWheelState(0)
		{
			for (int i = 0; i < LAST_MOUSE_BUTTON_VALUE; i++)
			{
				this->prevButtonState[i] = 0;
			}

			assert(Mouse::singetonInstance == nullptr);
			Mouse::singetonInstance = this;
		}

		Mouse::~Mouse()
		{
			assert(Mouse::singetonInstance != nullptr);
			Mouse::singetonInstance = nullptr;
		}







		void Mouse::UpdateStates()
		{
			for (int i = 0; i < LAST_MOUSE_BUTTON_VALUE; i++)
			{
				this->prevButtonState[i] = (char)glfwGetMouseButton(i);
			}

			this->prevWheelState = glfwGetMouseWheel();
		}







		// STATIC
		const bool Mouse::GetButton(const Input::MouseButton button)
		{
			if (glfwGetMouseButton(static_cast<int>(button)))
			{
				return true;
			}

			return false;
		}

		// STATIC
		const bool Mouse::GetButtonDown(const Input::MouseButton button)
		{
			const int buttonCode = static_cast<int>(button);
			const char currState = (char)glfwGetMouseButton(buttonCode);

			if (currState == GLFW_PRESS && singetonInstance->prevButtonState[buttonCode] != GLFW_PRESS)
			{
				return true;
			}

			return false;
		}

		// STATIC
		const bool Mouse::GetButtonUp(const Input::MouseButton button)
		{
			const int buttonCode = static_cast<int>(button);
			const char currState = (char)glfwGetMouseButton(buttonCode);

			if (currState == GLFW_RELEASE && singetonInstance->prevButtonState[buttonCode] != GLFW_RELEASE)
			{
				return true;
			}

			return false;
		}








		// STATIC
		void Mouse::GetMousePosition(float& x, float& y)
		{
			int ix = 0;
			int iy = 0;

			glfwGetMousePos(&ix, &iy);

			x = (float)ix;
			y = (float)iy;
		}

		// STATIC
		void Mouse::GetMousePosition(int& x, int& y)
		{
			glfwGetMousePos(&x, &y);
		}


		// STATIC
		const int Mouse::GetMousePositionXi()
		{
			int ix = 0;
			int iy = 0;

			glfwGetMousePos(&ix, &iy);

			iy;
			return ix;
		}

		// STATIC
		const int Mouse::GetMousePositionYi()
		{
			int ix = 0;
			int iy = 0;

			glfwGetMousePos(&ix, &iy);

			ix;
			return iy;
		}
		

		// STATIC
		const float Mouse::GetMousePositionXf()
		{
			int ix = 0;
			int iy = 0;

			glfwGetMousePos(&ix, &iy);

			iy;
			return (float)ix;
		}

		// STATIC
		const float Mouse::GetMousePositionYf()
		{
			int ix = 0;
			int iy = 0;

			glfwGetMousePos(&ix, &iy);

			ix;
			return (float)iy;
		}







		// STATIC
		const float Mouse::GetPositionNormalizedX()
		{
			const float xPos = Mouse::GetMousePositionXf();
			const float width = (float) Screen::GetWidth();

			return xPos / width;
		}
		
		// STATIC
		const float Mouse::GetPositionNormalizedY()
		{
			const float yPos = Mouse::GetMousePositionYf();
			const float height = (float) Screen::GetHeight();

			return yPos / height;
		}








		// STATIC
		const int Mouse::GetMouseWheel()
		{
			return glfwGetMouseWheel();
		}

		// STATIC
		// Gets the relative change in the mouse wheel per frame
		const int Mouse::GetMouseWheelDelta()
		{
			const int currMouseWheel = glfwGetMouseWheel();
			return currMouseWheel - Mouse::singetonInstance->prevWheelState;
		}

	}
}