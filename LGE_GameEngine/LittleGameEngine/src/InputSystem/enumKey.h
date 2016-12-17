#ifndef LGE_ENUM_KEY_H
#define LGE_ENUM_KEY_H
#include "GL\glfw.h"

namespace lge
{
	namespace Input
	{
		// Represents every usable key on the keyboard
		enum class Key
		{
			/* Printable keys (based off ISO 8859-1) */

			Space = GLFW_KEY_SPACE,
			Apostrophe = 39,		/* ' */
			Comma = 44,				/* , */
			Minus = 45,				/* - */
			Period = 46,			/* . */
			Slash = 47,				/* / */
			Number0 = 48,
			Number1 = 49,
			Number2 = 50,
			Number3 = 51,
			Number4 = 52,
			Number5 = 53,
			Number6 = 54,
			Number7 = 55,
			Number8 = 56,
			Number9 = 57,
			Semicolon = 59,			/* ; */
			Equal = 61,				/* = */
			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,
			BracketLeft = 91,		/* [ */
			BackSlash = 92,			/* \ */
			BracketRight = 93,		/* ] */
			GraveAccent = 96,		/* ` */
			WorldKey1 = 161,		/* non-US #1 */
			WorldKey2 = 162,		/* non-US #2 */

			/* Function keys */

			Escape = (GLFW_KEY_SPECIAL+1),
			F1 = (GLFW_KEY_SPECIAL + 2),
			F2 = (GLFW_KEY_SPECIAL + 3),
			F3 = (GLFW_KEY_SPECIAL + 4),
			F4 = (GLFW_KEY_SPECIAL + 5),
			F5 = (GLFW_KEY_SPECIAL + 6),
			F6 = (GLFW_KEY_SPECIAL + 7),
			F7 = (GLFW_KEY_SPECIAL + 8),
			F8 = (GLFW_KEY_SPECIAL + 9),
			F9 = (GLFW_KEY_SPECIAL + 10),
			F10 = (GLFW_KEY_SPECIAL + 11),
			F11 = (GLFW_KEY_SPECIAL + 12),
			F12 = (GLFW_KEY_SPECIAL + 13),
			F13 = (GLFW_KEY_SPECIAL + 14),
			F14 = (GLFW_KEY_SPECIAL + 15),
			F15 = (GLFW_KEY_SPECIAL + 16),
			F16 = (GLFW_KEY_SPECIAL + 17),
			F17 = (GLFW_KEY_SPECIAL + 18),
			F18 = (GLFW_KEY_SPECIAL + 19),
			F19 = (GLFW_KEY_SPECIAL + 20),
			F20 = (GLFW_KEY_SPECIAL + 21),
			F21 = (GLFW_KEY_SPECIAL + 22),
			F22 = (GLFW_KEY_SPECIAL + 23),
			F23 = (GLFW_KEY_SPECIAL + 24),
			F24 = (GLFW_KEY_SPECIAL + 25),
			F25 = (GLFW_KEY_SPECIAL + 26),
			ArrowUp = (GLFW_KEY_SPECIAL + 27),
			ArrowDown = (GLFW_KEY_SPECIAL + 28),
			ArrowLeft = (GLFW_KEY_SPECIAL + 29),
			ArrowRight = (GLFW_KEY_SPECIAL + 30),
			ShiftLeft = (GLFW_KEY_SPECIAL + 31),
			ShiftRight = (GLFW_KEY_SPECIAL + 32),
			ControlLeft = (GLFW_KEY_SPECIAL + 33),
			ControlRight = (GLFW_KEY_SPECIAL + 34),
			AltLeft = (GLFW_KEY_SPECIAL + 35),
			AltRight = (GLFW_KEY_SPECIAL + 36),
			Tab = (GLFW_KEY_SPECIAL + 37),
			Enter = (GLFW_KEY_SPECIAL + 38),
			Backspace = (GLFW_KEY_SPECIAL + 39),
			Insert = (GLFW_KEY_SPECIAL + 40),
			ForwardDelete = (GLFW_KEY_SPECIAL + 41),
			PageUp = (GLFW_KEY_SPECIAL + 42),
			PageDown = (GLFW_KEY_SPECIAL + 43),
			Home = (GLFW_KEY_SPECIAL + 44),
			End = (GLFW_KEY_SPECIAL + 45),
			Keypad0 = (GLFW_KEY_SPECIAL + 46),
			Keypad1 = (GLFW_KEY_SPECIAL + 47),
			Keypad2 = (GLFW_KEY_SPECIAL + 48),
			Keypad3 = (GLFW_KEY_SPECIAL + 49),
			Keypad4 = (GLFW_KEY_SPECIAL + 50),
			Keypad5 = (GLFW_KEY_SPECIAL + 51),
			Keypad6 = (GLFW_KEY_SPECIAL + 52),
			Keypad7 = (GLFW_KEY_SPECIAL + 53),
			Keypad8 = (GLFW_KEY_SPECIAL + 54),
			Keypad9 = (GLFW_KEY_SPECIAL + 55),
			KeypadDivide = (GLFW_KEY_SPECIAL + 56),
			KeypadMultiply = (GLFW_KEY_SPECIAL+57),
			KeypadSubtract = (GLFW_KEY_SPECIAL+58),
			KeypadAdd = (GLFW_KEY_SPECIAL + 59),
			KeypadDecimalPoint = (GLFW_KEY_SPECIAL + 60),
			KeypadEqual = (GLFW_KEY_SPECIAL + 61),
			KeypadEnter = (GLFW_KEY_SPECIAL + 62),
			NumberLock = (GLFW_KEY_SPECIAL+63),
			CapsLock = (GLFW_KEY_SPECIAL + 64),
			ScrollLock = (GLFW_KEY_SPECIAL+65),
			Pause = (GLFW_KEY_SPECIAL + 66),
			SuperLeft = (GLFW_KEY_SPECIAL + 67),
			SuperRight = (GLFW_KEY_SPECIAL + 68),
			Menu = (GLFW_KEY_SPECIAL + 69)
		};





		enum LGE_LAST_KEY
		{
			// Used for array iteration
			LAST_KEY_VALUE = GLFW_KEY_LAST + 1,
			// Used for array iteration
			FIRST_KEY_VALUE = GLFW_KEY_SPACE
		};
	}
}
#endif