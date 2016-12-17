#ifndef LGE_ENUM_MOUSE_BUTTON_H
#define LGE_ENUM_MOUSE_BUTTON_H
#include "GL\glfw.h"

namespace lge
{
	namespace Input
	{
		// Represents every usable mouse button (up to 8 buttons)
		enum class MouseButton
		{
			// Also Left
			B1 = GLFW_MOUSE_BUTTON_1,
			// Also Right
			B2 = GLFW_MOUSE_BUTTON_2,
			// Also Middle
			B3 = GLFW_MOUSE_BUTTON_3,
			
			B4 = GLFW_MOUSE_BUTTON_4,
			B5 = GLFW_MOUSE_BUTTON_5,
			B6 = GLFW_MOUSE_BUTTON_6,
			B7 = GLFW_MOUSE_BUTTON_7,
			B8 = GLFW_MOUSE_BUTTON_8,

			Left = GLFW_MOUSE_BUTTON_LEFT,
			Right = GLFW_MOUSE_BUTTON_RIGHT,
			Middle = GLFW_MOUSE_BUTTON_MIDDLE
		};



		enum LGE_LAST_MOUSE_BUTTON
		{
			// Used for array iteration
			LAST_MOUSE_BUTTON_VALUE = GLFW_MOUSE_BUTTON_LAST + 1
		};
	}
}
#endif