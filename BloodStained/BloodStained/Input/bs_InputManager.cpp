#include "bs_InputManager.h"


namespace bs
{
	Keyboard	InputManager::keyboard;
	Mouse		InputManager::mouse;


	void InputManager::update()
	{
		keyboard._setLastKeystates();
		mouse._setLastStates();
	}

}