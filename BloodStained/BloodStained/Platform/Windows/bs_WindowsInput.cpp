#include "bs_WindowsInput.h"
#include <Input/bs_InputManager.h>
#include <Utilities/bs_Error.h>

namespace bs
{
	ERROR_ID WindowsInput::initialize()
	{
		RAWINPUTDEVICE rid[2];

		rid[0].usUsagePage = 0x01;
		rid[0].usUsage = 0x02;
		rid[0].dwFlags = 0;
		rid[0].hwndTarget = 0;

		rid[1].usUsagePage = 0x01;
		rid[1].usUsage = 0x06;
		rid[1].dwFlags = 0;
		rid[1].hwndTarget = 0;

		CHAR name[KL_NAMELENGTH];
		LoadKeyboardLayoutA(name, NULL);

		

		if (RegisterRawInputDevices(rid, 2, sizeof(rid[0])) == FALSE)
		{
			return ERROR_ID::WINDOWS_RID_REGISTRATION_FAIL;
		}
		return ERROR_ID::NONE;
	}

	ERROR_ID WindowsInput::shutDown()
	{
		return ERROR_ID();
	}

	ERROR_ID WindowsInput::getRawInput(HWND hWnd, LPARAM lParam)
	{
		UINT size;
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));

		LPBYTE byteArray[128];

		if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, byteArray, &size, sizeof(RAWINPUTHEADER)) != size)
			return ERROR_ID::WINDOWS_RAWINPUT_FAIL;

		RAWINPUT* rawInput = (RAWINPUT*)byteArray;

		USHORT flags;

		//keyboard
		USHORT keyCode = 0;
		USHORT keyboardFlags = 0;

		//mouse
		ui32 x = 0;
		ui32 y = 0;
		ui32 newX = 0;
		ui32 newY = 0;
		
		switch (rawInput->header.dwType)
		{
		case RIM_TYPEMOUSE:
		{
			POINT screenToClient;

			GetCursorPos(&screenToClient);

			bool result = ScreenToClient(hWnd, &screenToClient);

			newX = (ui32)screenToClient.x;
			newY = (ui32)screenToClient.y;

			InputManager::mouse._setDeltaPosition((int)rawInput->data.mouse.lLastX, (int)rawInput->data.mouse.lLastY);
			InputManager::mouse._setPosition(newX, newY);

			flags = rawInput->data.mouse.usButtonFlags;
			if ((flags & RI_MOUSE_WHEEL) == RI_MOUSE_WHEEL)
				InputManager::mouse._setWheel((short)(rawInput->data.mouse.usButtonData));
			else InputManager::mouse._setButtons(flags);
		}
		break;
		case RIM_TYPEKEYBOARD:
			keyCode = rawInput->data.keyboard.VKey;

			keyboardFlags = rawInput->data.keyboard.Flags;

			if ((keyboardFlags & RI_KEY_MAKE) == RI_KEY_MAKE)
			{
				InputManager::keyboard._setKeyPressed(keyCode);
			}
			if ((keyboardFlags & RI_KEY_BREAK) == RI_KEY_BREAK)
			{
				InputManager::keyboard._setKeyReleased(keyCode);
			}
			break;
		}

		return ERROR_ID::NONE;
	}
}
