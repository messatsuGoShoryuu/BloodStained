#include "bs_WindowsInput.h"
#include "../../../Globals/bs_globals.h"
#include "../../../Rendering/bs_Screen.h"
#include "../bs_WindowsMain.h"
#include "../../../Rendering/bs_OpenGLWindow.h"

namespace bs
{
	HANDLE*		WindowsInput::sm_indexTable;
	ui8			WindowsInput::sm_indexCounter;
	ui16		WindowsInput::sm_lastPressedKeyboardKey = 0;

	bool		g_cursor = true;

	void showCursor(bool value)
	{
		if (g_cursor != value)
		{
			g_cursor = value;
			ShowCursor(value);
		}
	}

	bool  WindowsInput::initialize()
	{
		sm_indexTable = (HANDLE*)BS_Malloc(sizeof(HANDLE) * 16);
		sm_indexCounter = 0;
		registerJoysticks();
		if(!registerMouseAndKeyboard()) return false;
		getAttachedDevices();
	//	getRegisteredDevices();

		return true;
	}

	bool WindowsInput::shutDown()
	{
		if (sm_indexTable)
		BS_Free(sm_indexTable);
		return true;
	}

	bool WindowsInput::registerJoysticks()
	{
		RAWINPUTDEVICE rid[2];
		rid[0].usUsagePage = 0x01;
		rid[0].usUsage = 0x05;
		rid[0].dwFlags = 0;                 // adds game pad
		rid[0].hwndTarget = 0;

		rid[1].usUsagePage = 0x01;
		rid[1].usUsage = 0x04;
		rid[1].dwFlags = 0;                 // adds joystick
		rid[1].hwndTarget = 0;


		//register joysticks
		if (!RegisterRawInputDevices(rid, 1, sizeof(RAWINPUTDEVICE)))
		{
			//			warnConsole("No joystick found");
			std::cout << "ERROR = " << GetLastError() << std::endl;;
		}

		//register gamepads
		if (!RegisterRawInputDevices(&rid[1], 1, sizeof(RAWINPUTDEVICE)))
		{
			//			warnConsole("No gamepad found");
			std::cout << "ERROR = " << GetLastError() << std::endl;;
		}

		return true;
	}

	bool WindowsInput::registerMouseAndKeyboard()
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

		g_inputManager.keyboard.setLayoutName(name);
		std::cout << "layout name loading successful : " << GetKeyboardLayoutNameA(name) << std::endl;

		std::cout << "keyboard layout name = " << name << std::endl;

		if (RegisterRawInputDevices(rid, 2, sizeof(rid[0])) == FALSE)
		{
			std::cout << "ERROR REGISTERING INPUT DEVICES" << std::endl;
			return false;
		}
		return true;
	}

	bool WindowsInput::getRegisteredDevices()
	{
		RAWINPUTDEVICE* rid = NULL;
		UINT			inputDeviceNumber = 0;
		UINT error = GetRegisteredRawInputDevices(NULL, &inputDeviceNumber, sizeof(RAWINPUTDEVICE));
		if (error < 0)
		{
			return false;
		}

		rid = (RAWINPUTDEVICE*)BS_Malloc(sizeof(RAWINPUTDEVICE) * inputDeviceNumber);

		error = GetRegisteredRawInputDevices(rid, &inputDeviceNumber, sizeof(RAWINPUTDEVICE));

		if (error < 0)
		{
			std::cout << "ERROR REGISTERING INPUT DEVICES" << std::endl;
			BS_Free(rid);
			return false;
		}
		BS_Free(rid);
		return true;
	}

	bool WindowsInput::getInput(LPARAM& lParam)
	{
		UINT size;
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));

		LPBYTE byteArray[128];

		if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, byteArray, &size, sizeof(RAWINPUTHEADER)) != size)
			return false;

		RAWINPUT* rawInput = (RAWINPUT*)byteArray;

		//mouse
		ui32 x = 0;
		ui32 y = 0;
		ui32 newX = 0;
		ui32 newY = 0;


		USHORT flags;

		//keyboard
		USHORT keyCode = 0;
		USHORT keyboardFlags = 0;
		OpenGLWindow* w = (OpenGLWindow*)g_game.window();
		
		switch (rawInput->header.dwType)
		{
			case RIM_TYPEMOUSE:



	//			if (g_screen.isWindowed())
				{

					POINT screenToClient;


					GetCursorPos(&screenToClient);
					
					bool result = ScreenToClient(w->hwnd(), &screenToClient);

					newX = (ui32)screenToClient.x;
					newY = (ui32)screenToClient.y;

			//		if (newX >= g_screen.width()) showCursor(true);
			//		else if (newY >= g_screen.height()) showCursor(true);
			//		else showCursor(false);

				}
				/*
				else
				{
					x = g_inputManager.mouse.getX();
					y = g_inputManager.mouse.getY();

					newX = x + rawInput->data.mouse.lLastX;
					newY = y + rawInput->data.mouse.lLastY;

					if (newX >= g_screen.width()) newX = x;
					if (newY >= g_screen.height()) newY = y;
				}
				*/

				g_inputManager.mouse.setDeltaPosition((int)rawInput->data.mouse.lLastX, (int)rawInput->data.mouse.lLastY);


				g_inputManager.mouse.setPosition(newX, newY);



				flags = rawInput->data.mouse.usButtonFlags;
				if ((flags & RI_MOUSE_WHEEL) == RI_MOUSE_WHEEL)
					g_inputManager.mouse.setWheel((short)(rawInput->data.mouse.usButtonData));
				else g_inputManager.mouse.setButtons(flags);

				break;
			case RIM_TYPEKEYBOARD:
				keyCode = rawInput->data.keyboard.VKey;

				keyboardFlags = rawInput->data.keyboard.Flags;

				if ((keyboardFlags & RI_KEY_MAKE) == RI_KEY_MAKE)
				{
					g_inputManager.keyboard._pushToPressBuffer(keyCode);
					if (keyCode != sm_lastPressedKeyboardKey || keyCode == KB_BACKSPACE)
					{
						g_inputManager.keyboard.m_lastPressedKey = keyCode;
					}

					sm_lastPressedKeyboardKey = keyCode;
				}
				if ((keyboardFlags & RI_KEY_BREAK) == RI_KEY_BREAK)
				{
					g_inputManager.keyboard._pushToReleaseBuffer(keyCode);
				}
				break;
			case RIM_TYPEHID:
				break;
		}

		return true;
	}

	void WindowsInput::addJoystick(const Joystick& joystick, HANDLE& handle)
	{
		if (sm_indexCounter >= 16)
		{
			std::cout << "No more joysticks are allowed" << std::endl;
			return;
		}
		size_t index = g_inputManager.m_joysticks.add(joystick);
		if (index < 16)
		{
			sm_indexTable[index] = handle;
			sm_indexCounter++;
		}
		else
		{
			std::cout << "No more joysticks are allowed" << std::endl;
			return;
		}
	}

	bool WindowsInput::getAttachedDevices()
	{
		PRAWINPUTDEVICELIST rid = NULL;
		UINT number = 0;

		if (GetRawInputDeviceList(NULL, &number, sizeof(RAWINPUTDEVICELIST)) != 0) { return false; }
		rid = (PRAWINPUTDEVICELIST)BS_Malloc(sizeof(RAWINPUTDEVICELIST)* number);
		if (!rid) 
		{
			BS_Free(rid);
			return false; 
		}

		ui32 error = GetRawInputDeviceList(rid, &number, sizeof(RAWINPUTDEVICELIST));

		if (error < 0)
		{
			BS_Free(rid);
			return false;
		}

		for (UINT i = 0; i < number; i++)
		{
			RID_DEVICE_INFO info;
			info.cbSize = sizeof(RID_DEVICE_INFO);
			UINT characterCount = 0;
			error = GetRawInputDeviceInfo(rid[i].hDevice, RIDI_DEVICENAME, NULL, &characterCount);

			if (error < 0)
			{
				String errString("Could not get device name character count for device no.");
				errString = errString + (i32)i;

				std::cout << (errString.utf8()) << std::endl;
				continue;
			}

			wchar_t*	deviceName = (wchar_t*)BS_Malloc(sizeof(wchar_t) * characterCount);

			error = GetRawInputDeviceInfo(rid[i].hDevice, RIDI_DEVICENAME, deviceName, &characterCount);

			if (error < 0)
			{
				String errString("Could not get device name character count for device no.");
				errString = errString + (i32)i;

				BS_Free(deviceName);

				std::cout << (errString.utf8()) << std::endl;
				continue;
			}



			error = GetRawInputDeviceInfo(rid[i].hDevice, RIDI_DEVICEINFO, &info, (PUINT)&info.cbSize);

			if (error < 0)
			{
				String errString("Could not get device name character count for device no.");
				errString = errString + (i32)i;

				std::cout << (errString.utf8()) << std::endl;
			}


			if (info.dwType == RIM_TYPEHID)
			{
				if (info.hid.usUsage == 0x05 && info.hid.usUsagePage == 0x01)
				{

					Joystick joystick;
					//@todo: set joystick name
					addJoystick(joystick, rid[i].hDevice);
				}
			}

			if (deviceName) BS_Free(deviceName);
		}

		if (rid) BS_Free(rid);

		return true;
	}
}