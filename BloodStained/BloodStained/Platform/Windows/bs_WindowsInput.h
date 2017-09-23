#ifndef _BS_WINDOWSINPUT_H_
#define _BS_WINDOWSINPUT_H_

#include <Windows.h>

namespace bs
{
	enum class ERROR_ID;

	class WindowsInput
	{
	public:
		static ERROR_ID initialize();
		static ERROR_ID shutDown();

		static ERROR_ID getRawInput(HWND hWnd, LPARAM lParam);
	};
}

#endif // !_BS_WINDOWSINPUT_H_