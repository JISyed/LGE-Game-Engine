#include "Keyboard.h"
#include <cassert>
#include "GL\glfw.h"

namespace lge
{
	namespace Input
	{
		//
		// Static Data
		//
		Keyboard* Keyboard::singetonInstance = nullptr;



		//
		// Methods
		//

		Keyboard::Keyboard()
		{
			for (int i = 0; i < LAST_KEY_VALUE; i++)
			{
				this->prevKeyState[i] = 0;
			}

			// Register the singleton pointer (only Game should be calling the constructor)
			assert(Keyboard::singetonInstance == nullptr);
			Keyboard::singetonInstance = this;
		}

		Keyboard::~Keyboard()
		{
			assert(Keyboard::singetonInstance != nullptr);
			Keyboard::singetonInstance = nullptr;
		}




		void Keyboard::UpdateStates()
		{
			for (int i = FIRST_KEY_VALUE; i < LAST_KEY_VALUE; i++)
			{
				this->prevKeyState[i] = (char) glfwGetKey(i);
			}
		}




		// STATIC
		const bool Keyboard::GetKey(const Input::Key key)
		{
			if (glfwGetKey(static_cast<int>(key)) == GLFW_PRESS)
			{
				return true;
			}

			return false;
		}

		// STATIC
		const bool Keyboard::GetKeyDown(const Input::Key key)
		{
			const int keyCode = static_cast<int>(key);
			const char currState = (char)glfwGetKey(keyCode);

			if (currState == GLFW_PRESS && singetonInstance->prevKeyState[keyCode] != GLFW_PRESS)
			{
				return true;
			}

			return false;
		}

		// STATIC
		const bool Keyboard::GetKeyUp(const Input::Key key)
		{
			const int keyCode = static_cast<int>(key);
			const char currState = (char)glfwGetKey(keyCode);

			if (currState == GLFW_RELEASE && singetonInstance->prevKeyState[keyCode] != GLFW_RELEASE)
			{
				return true;
			}

			return false;
		}



	}
}