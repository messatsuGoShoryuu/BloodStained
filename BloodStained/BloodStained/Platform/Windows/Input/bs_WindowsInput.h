#ifndef BS_WINDOWSINPUT_H
#define BS_WINDOWSINPUT_H

#include <Windows.h>
#include"../../../Utilities/bs_types.h"

//this class provides communication between the input manager and the WIN32 API
namespace bs
{
	class WindowsInput
	{
	public:
		static bool initialize();
		static bool shutDown();
		static bool getInput(LPARAM& lParam);
	private:
		static bool registerMouseAndKeyboard();
		static bool registerJoysticks();
		static bool getRegisteredDevices();
		static void addJoystick(const class Joystick& joystick, HANDLE& handle);
		static bool getAttachedDevices();

		//joystick indexes
		static HANDLE*	sm_indexTable;
		static ui8		sm_indexCounter;

		static ui16		sm_lastPressedKeyboardKey;
	};
}
#endif // !BS_WINDOWSINPUT_H
