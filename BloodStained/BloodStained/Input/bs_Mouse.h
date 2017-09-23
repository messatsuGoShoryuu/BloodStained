#ifndef _BS_MOUSE_H_
#define _BS_MOUSE_H_

#include <Platform/bs_Platform.h>
#include <Utilities/bs_types.h>
#include <Utilities/bs_String.h>

#ifdef BS_WINDOWS
#include <Platform/Windows/bs_WindowsKeyboard.h>
#endif

namespace bs
{
	class Mouse
	{
#ifdef BS_WINDOWS
		friend class WindowsInput;
#endif
		friend class InputManager;
	public:
		Mouse();
		~Mouse();

		bool isButtonPressed(ui32 button);
		bool isButtonReleased(ui32 button);
		bool isButtonHeld(ui32 button);

		ui32 getX();
		ui32 getY();
		ui32 getLastX();
		ui32 getLastY();
		i16  getDeltaX();
		i16  getDeltaY();
		i16 getDeltaWheel();
	private:
		void _setPosition(ui32 x, ui32 y);
		void _setLastStates();
		void _setDeltaPosition(i32 deltaX, i32 deltaY);
		void _setButtons(ui16 buttons);
		void _setWheel(i16 value);
		void _setLastDeltas();

		short m_deltaWheel;
		byte m_buttons;
		byte m_lastButtons;
		//x = m_position & 4095;
		//y = m_position << 16;
		//y = y & 4095;
		ui32 m_position;
		ui32 m_lastPosition;
		i32	 m_deltaPosition;
		bool m_isDirty;
	};
}
#endif // !_BS_MOUSE_H_