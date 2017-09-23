#ifndef _BS_INPUTMANAGER_H_
#define _BS_INPUTMANAGER_H_

#include "bs_Keyboard.h"
#include "bs_Mouse.h"

#define MOUSE_BUTTON_1 0x01
#define MOUSE_BUTTON_2 0x02
#define INVALID_KEYCODE 0xFFFF

namespace bs
{
	enum class ERROR_ID;

	class InputManager
	{
	public:
		static	ERROR_ID initialize();
		static	ERROR_ID shutDown();

		static void update();
		static	Keyboard keyboard;

		static	Mouse mouse;
	};
}

#endif // !_BS_INPUTMANAGER_H_
